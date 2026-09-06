"""Exercise the personal CX-5 cluster patch through the controller and CAN decoder."""
import pytest

from opendbc.car import Bus, structs
from opendbc.car.mazda.carcontroller import CarController
from opendbc.car.mazda.tests.conftest import (CAM_LANEINFO, DBC_NAME, VisualAlert, car_control, car_control_sp,
                                            car_params, car_params_sp, mazda_car_state, parse_frame)
from opendbc.car.mazda.values import CAR, STEER_TO_ZERO_EPS_FW


def cluster_frame(candidate, firmware, alpha_long, fault, allowed_speed, visual_alert=VisualAlert.steerRequired):
  car_fw = []
  if firmware is not None:
    fw = structs.CarParams.CarFw()
    fw.ecu = structs.CarParams.Ecu.eps
    fw.address = 0x730
    fw.fwVersion = firmware
    car_fw.append(fw)
  cp = car_params(candidate, car_fw=car_fw, alpha_long=alpha_long)
  cp_sp = car_params_sp(cp, candidate, car_fw=car_fw, alpha_long=alpha_long)
  controller = CarController({Bus.pt: DBC_NAME}, cp, cp_sp)
  cs = mazda_car_state(cp, cp_sp, lkas_allowed_speed=allowed_speed)
  if fault is not None:
    setattr(cs.out, fault, True)
  cs.cam_laneinfo.update({"ERR_BIT": 1, "NO_ERR_BIT": 0, "LANE_LINES": 2})
  cc = car_control(long_active=alpha_long, lat_active=True, torque=0.3, visual_alert=visual_alert)
  _, sends = controller.update(cc, car_control_sp(), cs, 0)
  assert cc.hudControl.visualAlert == visual_alert  # comma still receives the original alert
  frames = [frame for frame in sends if frame[0] == CAM_LANEINFO and frame[2] == 0]
  assert len(frames) == 1
  return parse_frame(CAM_LANEINFO, frames[0][1])


@pytest.mark.parametrize("firmware", sorted(STEER_TO_ZERO_EPS_FW))
@pytest.mark.parametrize("alpha_long", [False, True])
@pytest.mark.parametrize("allowed_speed", [False, True])
@pytest.mark.parametrize("fault", [None, "steerFaultTemporary", "steerFaultPermanent"])
def test_swapped_cx5_silences_only_generic_cluster_takeover(firmware, alpha_long, allowed_speed, fault):
  out = cluster_frame(CAR.MAZDA_CX5, firmware, alpha_long, fault, allowed_speed)
  warning = fault is not None
  assert out["HANDS_ON_STEER_WARN"] == warning
  assert out["HANDS_ON_STEER_WARN_2"] == warning
  assert out["HANDS_WARN_3_BITS"] == (7 if warning else 0)
  assert out["ERR_BIT"] == 1 and out["NO_ERR_BIT"] == 0 and out["LANE_LINES"] == 2


@pytest.mark.parametrize("fault", ["steerFaultTemporary", "steerFaultPermanent"])
def test_swapped_cx5_fault_reaches_cluster_without_generic_visual_alert(fault):
  out = cluster_frame(CAR.MAZDA_CX5, sorted(STEER_TO_ZERO_EPS_FW)[0], False, fault, False, VisualAlert.none)
  assert out["HANDS_ON_STEER_WARN"] == 1


@pytest.mark.parametrize("candidate", [CAR.MAZDA_CX5, CAR.MAZDA_CX5_2022])
@pytest.mark.parametrize("allowed_speed", [False, True])
def test_unswapped_models_keep_upstream_cluster_behavior(candidate, allowed_speed):
  out = cluster_frame(candidate, None, False, None, allowed_speed)
  assert out["HANDS_ON_STEER_WARN"] == allowed_speed
