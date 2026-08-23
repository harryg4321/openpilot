"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

# Stands a fingerprinted car up in ui_state with synthetic vehicleInfoSP readings. Shared by the
# MICI settings tests and the screenshot harness so the two cannot drift from the wire shape.

from openpilot.cereal import custom, messaging
from opendbc.car.structs import car
from opendbc.sunnypilot.car.vehicle_info import get_vehicle_info_items
from opendbc.sunnypilot.car.vehicle_info_base import VehicleInfoItem


class FakeSubMaster(dict):
  """Enough of a SubMaster for the vehicle menu: it reads one service, three ways."""

  def __init__(self, msgs, updated: bool = True, valid: bool = True):
    super().__init__(msgs)
    self.updated = dict.fromkeys(msgs, updated)
    self.valid = dict.fromkeys(msgs, valid)


def stub_vehicle_info(values: dict[str, float], fingerprint: str = "MAZDA_CX5_2022",
                      brand: str = "mazda", started: bool = True, metric: bool = False,
                      valid: bool = True) -> list[VehicleInfoItem]:
  """Point ui_state at `fingerprint` publishing `values`. Keys absent from `values` are published
  as unavailable, which is what a car that does not broadcast that signal looks like."""
  from openpilot.selfdrive.ui.ui_state import ui_state

  ui_state.CP = car.CarParams.new_message(carFingerprint=fingerprint, brand=brand,
                                          enableBsm=True, steerControlType="torque")
  ui_state.CP_SP = custom.CarParamsSP.new_message()
  ui_state.started = started
  ui_state.is_metric = metric

  items = get_vehicle_info_items(ui_state.CP, ui_state.CP_SP)
  msg = messaging.new_message("vehicleInfoSP")
  msg.vehicleInfoSP.values = [{"key": i.key, "value": float(values.get(i.key, 0.0)),
                               "valid": i.key in values} for i in items]
  ui_state.sm = FakeSubMaster({"vehicleInfoSP": msg.vehicleInfoSP}, valid=valid)
  return items
