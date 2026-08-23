"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.widgets.list_view import ButtonAction
from openpilot.system.ui.widgets.scroller_tici import Scroller

from openpilot.selfdrive.ui.sunnypilot.layouts.settings.vehicle.brands.factory import BrandSettingsFactory
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.vehicle.platform_selector import PlatformSelector, LegendWidget
from openpilot.selfdrive.ui.sunnypilot.lib.vehicle_info import GROUP_LABELS, VehicleInfoModel, set_active
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.sunnypilot.lib.styles import style
from openpilot.system.ui.sunnypilot.widgets.list_view import ListItemSP


class VehicleLayout(Widget):
  def __init__(self):
    super().__init__()
    self._brand_settings = None
    self._brand_items = []
    self._current_brand = None
    self._platform_selector = PlatformSelector(self._update_brand_settings)
    self._vehicle_info = VehicleInfoModel()

    self._vehicle_item = ListItemSP(title=self._platform_selector.text, action_item=ButtonAction(text=tr("SELECT")),
                                    callback=self._platform_selector._on_clicked)
    self._vehicle_item.title_color = self._platform_selector.color
    self._legend_widget = LegendWidget(self._platform_selector)

    self.items = [self._vehicle_item, self._legend_widget]
    self._scroller = Scroller(self.items, line_separator=True, spacing=0)

  @staticmethod
  def get_brand():
    if bundle := ui_state.params.get("CarPlatformBundle"):
      return bundle.get("brand", "")
    elif ui_state.CP is not None and ui_state.CP.carFingerprint != "MOCK":
      return ui_state.CP.brand
    return ""

  def _vehicle_info_items(self) -> list:
    """Live DBC readings for this platform, one section per group. Values resolve on render, so
    the rows only have to be rebuilt when the car itself changes.

    No explicit separators: this panel's Scroller draws its own between every item, unlike the
    steering panel, which turns them off and places LineSeparatorSP by hand."""
    items: list = []
    for group, group_items in self._vehicle_info.by_group.items():
      items.append(ListItemSP(title=tr(GROUP_LABELS[group]), title_color=style.ITEM_TEXT_VALUE_COLOR))
      for item in group_items:
        row = ListItemSP(title=tr(item.label))
        row.set_right_value(lambda i=item: self._vehicle_info.format(i))
        items.append(row)
    return items

  def _update_brand_settings(self):
    self._vehicle_item._title = self._platform_selector.text
    self._vehicle_item.title_color = self._platform_selector.color
    vehicle_text = tr("REMOVE") if ui_state.params.get("CarPlatformBundle") else tr("SELECT")
    self._vehicle_item.action_item.set_text(vehicle_text)

    self._vehicle_info.update()

    brand = self.get_brand()
    if brand != self._current_brand or self._vehicle_info.changed:
      self._current_brand = brand
      self._brand_settings = BrandSettingsFactory.create_brand_settings(brand)
      self._brand_items = self._brand_settings.items if self._brand_settings else []

      self.items = [self._vehicle_item, self._legend_widget] + self._brand_items + self._vehicle_info_items()
      self._scroller = Scroller(self.items, line_separator=True, spacing=0)

  def _update_state(self):
    self._update_brand_settings()
    if self._brand_settings:
      self._brand_settings.update_settings()
    self._platform_selector.refresh()

  def _render(self, rect):
    self._scroller.render(rect)

  def show_event(self):
    self._scroller.show_event()
    set_active(True)

  def hide_event(self):
    super().hide_event()
    set_active(False)
