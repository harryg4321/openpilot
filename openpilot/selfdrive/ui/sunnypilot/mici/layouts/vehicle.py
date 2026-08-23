"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

from openpilot.selfdrive.ui.mici.widgets.button import BigButton
from openpilot.selfdrive.ui.sunnypilot.lib.vehicle_info import GROUP_LABELS, VehicleInfoModel, set_active
from openpilot.selfdrive.ui.sunnypilot.mici.widgets.button import BigButtonSP, SubPanelSP
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets.scroller import NavScroller
from opendbc.sunnypilot.car.vehicle_info_base import ItemGroup, ItemType, VehicleInfoItem

# a group button summarizes itself with this many readings, or this many raised flags
SUMMARY_LIMIT = 2
FLAG_LIMIT = 3


class VehicleInfoRow(BigButton):
  """A read-only row: the item's label, with its live value as the subtitle."""

  def __init__(self, model: VehicleInfoModel, item: VehicleInfoItem):
    super().__init__(tr(item.label))
    self._model = model
    self._item = item
    self.set_enabled(False)
    self.refresh()

  def refresh(self) -> None:
    value = self._model.format(self._item)
    if value != self.value:
      self.set_value(value)


class VehicleLayoutMici(NavScroller):
  """Read-only view of what the car broadcasts, grouped into sub-panels.

  The rows come from the platform's vehicle-info declaration, so they are only known once the
  car is fingerprinted. The panel is built the first time a fingerprint appears and rebuilt if
  it changes, which happens when the platform is overridden by hand.
  """

  def __init__(self):
    super().__init__()

    self._model = VehicleInfoModel()
    self._group_buttons: dict[ItemGroup, BigButtonSP] = {}
    self._group_views: dict[ItemGroup, SubPanelSP] = {}
    # headline rows per group, fixed for a given car, so _summarize does no scanning per frame
    self._group_readings: dict[ItemGroup, list[VehicleInfoItem]] = {}

    self._placeholder = BigButtonSP(tr("no vehicle data"), tr("nothing is mapped for this car yet"))
    self._placeholder.set_enabled(False)
    self._placeholder.set_subtitle_font_size(24)
    self._scroller.add_widget(self._placeholder)

  def _build(self) -> None:
    self._group_buttons.clear()
    self._group_views.clear()
    self._group_readings.clear()

    for group, items in self._model.by_group.items():
      btn = BigButtonSP(tr(GROUP_LABELS[group]))
      btn.set_subtitle_font_size(24)
      self._group_views[group] = btn.link_sub_panel([VehicleInfoRow(self._model, i) for i in items])
      self._group_buttons[group] = btn
      self._group_readings[group] = [i for i in items if i.type != ItemType.flag][:SUMMARY_LIMIT]

    self._scroller._items.clear()
    self._scroller.add_widgets(list(self._group_buttons.values()) or [self._placeholder])

  def _summarize(self, group: ItemGroup) -> None:
    """Headline readings for the group, else whichever of its flags are raised."""
    btn = self._group_buttons[group]

    readings = self._group_readings[group]
    if readings:
      btn.set_badges([(self._model.format(i), "on") for i in readings])
      return

    raised = [i for i in self._model.by_group[group] if self._model.is_on(i)][:FLAG_LIMIT]
    if raised:
      btn.set_badges([(tr(i.label), "on") for i in raised])
    elif self._model.live:
      btn.set_value(tr("all clear"))
    else:
      btn.set_disabled()

  def show_event(self) -> None:
    super().show_event()
    set_active(True)

  def hide_event(self) -> None:
    super().hide_event()
    set_active(False)

  def _update_state(self) -> None:
    super()._update_state()

    self._model.update()
    if self._model.changed:
      self._build()

    for group in self._group_buttons:
      self._summarize(group)
