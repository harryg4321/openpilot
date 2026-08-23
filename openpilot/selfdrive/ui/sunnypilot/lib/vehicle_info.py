"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

# Shared, layout-independent half of the vehicle menu: what rows the car has, and how to turn a
# published value into a string. Both the MICI and the TICI panel build on this, so the two can
# only disagree about layout, never about content or units.

from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.multilang import tr, tr_noop
from opendbc.sunnypilot.car.vehicle_info import get_item_states, get_vehicle_info_items
from opendbc.sunnypilot.car.vehicle_info_base import ItemGroup, ItemType, Unit, VehicleInfoItem

UNAVAILABLE = "--"

# card parses the car's vehicle-info signals only while this is set: it is a second pass over
# every CAN frame, and nothing but this menu consumes it. A panel that misses its hide event
# (a UI crash) just leaves card parsing until the next boot, which is where it started.
ACTIVE_PARAM = "VehicleInfoActive"

# Group names are translatable. Item labels are not: they live in the platform's declaration
# over in opendbc, which cannot import the UI, so tr() sees a variable and the extractor never
# finds them. They fall back to English, which suits DBC-derived terms well enough.
GROUP_LABELS: dict[ItemGroup, str] = {
  ItemGroup.powertrain: tr_noop("powertrain"),
  ItemGroup.chassis: tr_noop("chassis"),
  ItemGroup.body: tr_noop("body"),
  ItemGroup.assist: tr_noop("driver assist"),
}


def set_active(active: bool) -> None:
  """Call from the panel's show/hide events. Non-blocking: a frame of lag costs nothing."""
  ui_state.params.put_bool(ACTIVE_PARAM, active)


class VehicleInfoModel:
  """Rows for the current car, kept in sync with vehicleInfoSP.

  Rebuilds when the fingerprinted car changes, which on a device happens once per boot but in the
  settings UI can also happen when the platform is overridden by hand. `changed` reports whether
  the last update() rebuilt, so a layout can drop its widgets without tracking the car itself.
  """

  def __init__(self):
    self._fingerprint: str | None = None
    self.by_group: dict[ItemGroup, list[VehicleInfoItem]] = {}
    self.changed: bool = False
    self.live: bool = False
    self._states: dict[str, dict[int, str]] = {}
    self._values: dict[str, float] = {}

  @property
  def items(self) -> list[VehicleInfoItem]:
    return [i for group in self.by_group.values() for i in group]

  @property
  def available(self) -> bool:
    return bool(self.by_group)

  def update(self) -> None:
    CP, CP_SP = ui_state.CP, ui_state.CP_SP
    fingerprint = CP.carFingerprint if CP is not None else None

    self.changed = fingerprint != self._fingerprint
    if self.changed:
      self._fingerprint = fingerprint
      items = get_vehicle_info_items(CP, CP_SP) if (CP is not None and CP_SP is not None) else []
      # declaration order is the display order, both within a group and between groups
      self.by_group = {}
      for item in items:
        self.by_group.setdefault(item.group, []).append(item)
      self._states = {i.key: get_item_states(CP, i) for i in items if i.type == ItemType.state}
      self._values = {}

    if ui_state.sm.updated["vehicleInfoSP"]:
      # copy out rather than holding readers into the SubMaster's buffer, which is replaced
      # underneath us on the next receive. Invalid reads the same as absent, so drop it here.
      self._values = {v.key: float(v.value) for v in ui_state.sm["vehicleInfoSP"].values if v.valid}

    # a car that is off publishes nothing, so drop stale readings rather than freeze them
    if not ui_state.started:
      self._values = {}

    self.live = ui_state.sm.valid["vehicleInfoSP"] and bool(self._values)

  def raw(self, item: VehicleInfoItem) -> float | None:
    """The published value, or None while the signal is unavailable."""
    return self._values.get(item.key)

  def is_on(self, item: VehicleInfoItem) -> bool:
    return bool(self.raw(item))

  def format(self, item: VehicleInfoItem) -> str:
    value = self.raw(item)
    if value is None:
      return UNAVAILABLE

    if item.type == ItemType.flag:
      return tr("on") if value else tr("off")

    if item.type == ItemType.state:
      state = self._states.get(item.key, {})
      return tr(state[int(value)]) if int(value) in state else str(int(value))

    return _format_number(value, item)


def _format_number(value: float, item: VehicleInfoItem) -> str:
  if item.unit == Unit.celsius:
    if ui_state.is_metric:
      return f"{value:.{item.decimals}f} {tr('°C')}"
    return f"{value * 9.0 / 5.0 + 32.0:.{item.decimals}f} {tr('°F')}"

  text = f"{value:.{item.decimals}f}"
  return f"{text} {tr('rpm')}" if item.unit == Unit.rpm else text
