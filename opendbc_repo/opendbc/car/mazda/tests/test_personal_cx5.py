"""Contract for this private branch: one 2021 CX-5 with a confirmed 2022 EPS."""
import pytest

from opendbc.car import structs
from opendbc.car.fw_versions import match_fw_to_car
from opendbc.car.mazda.carcontroller import VisualAlert, _steer_required_alert
from opendbc.car.mazda.fingerprints import FW_VERSIONS
from opendbc.car.mazda.interface import CarInterface
from opendbc.car.mazda.values import CAR, CarControllerParams, MazdaFlags, MazdaSafetyFlags, STEER_TO_ZERO_EPS_FW

Ecu = structs.CarParams.Ecu
DONOR_EPS = sorted(STEER_TO_ZERO_EPS_FW)[0]
VIN_2021 = 'JM3KF2L50M0000042'


def _fw(ecu, address, version):
  fw = structs.CarParams.CarFw()
  fw.ecu = ecu
  fw.address = address
  fw.subAddress = 0
  fw.fwVersion = version
  fw.brand = 'mazda'
  return fw


def _firmware(case):
  if case == 'missing':
    return []
  eps = _fw(Ecu.eps, 0x730, DONOR_EPS)
  if case == 'eps_only':
    return [eps]
  if case == 'unknown_engine':
    return [eps, _fw(Ecu.engine, 0x7e0, b'UNKNOWN-ENGINE')]
  if case == '2022_engine':
    return [eps, _fw(Ecu.engine, 0x7e0, FW_VERSIONS[CAR.MAZDA_CX5_2022][(Ecu.engine, 0x7e0, None)][0])]
  assert case == 'known_old_firmware'
  return [_fw(ecu, address, DONOR_EPS if ecu == Ecu.eps else versions[0])
          for (ecu, address, _), versions in FW_VERSIONS[CAR.MAZDA_CX5].items()]


def _params(candidate, car_fw, alpha_long):
  return CarInterface.get_params(candidate, {0: {}, 1: {}, 2: {}}, car_fw, alpha_long, is_release=False, docs=False)


def _assert_personal(CP, alpha_long):
  assert CP.carFingerprint == CAR.MAZDA_CX5
  assert CP.flags & MazdaFlags.EPS_SWAP_CX5
  assert not CP.dashcamOnly
  assert CP.minSteerSpeed == 0
  assert CP.steerActuatorDelay == pytest.approx(0.14)
  assert CP.alphaLongitudinalAvailable
  assert CP.openpilotLongitudinalControl == alpha_long
  assert CP.safetyConfigs[0].safetyModel == structs.CarParams.SafetyModel.mazda
  assert CP.safetyConfigs[0].safetyParam == (MazdaSafetyFlags.LONG if alpha_long else 0)
  assert not _steer_required_alert(CP, VisualAlert.steerRequired, True, False)
  # A real temporary steering fault must still reach the cluster, at either speed gate.
  for allowed_speed in (False, True):
    assert _steer_required_alert(CP, VisualAlert.none, allowed_speed, True)
  limits = CarControllerParams(CP)
  assert limits.STEER_MAX_LOOKUP == ([0., 14.2, 14.5], [1200, 1200, 800])
  assert (limits.STEER_DELTA_UP, limits.STEER_DELTA_DOWN, limits.STEER_DRIVER_MULTIPLIER) == (12, 25, 15)
  assert (limits.ACCEL_MIN, limits.ACCEL_MAX) == (-3.5, 2.0)


@pytest.mark.parametrize('alpha_long', [False, True])
@pytest.mark.parametrize('fw_case', ['missing', 'eps_only', 'unknown_engine', '2022_engine', 'known_old_firmware'])
def test_personal_cx5_has_one_explicit_configuration(alpha_long, fw_case):
  car_fw = _firmware(fw_case)
  CP = _params(CAR.MAZDA_CX5, car_fw, alpha_long)
  _assert_personal(CP, alpha_long)
  expected = _params(CAR.MAZDA_CX5, [], alpha_long)
  assert CP.to_dict() == expected.to_dict()
  CP_SP = CarInterface.get_params_sp(CP, CAR.MAZDA_CX5, {0: {}, 1: {}, 2: {}}, car_fw, alpha_long, False, False)
  assert CP_SP.intelligentCruiseButtonManagementAvailable
  assert CP_SP == CarInterface.get_params_sp(expected, CAR.MAZDA_CX5, {0: {}, 1: {}, 2: {}}, [], alpha_long, False, False)
  CI = CarInterface(CP, CP_SP)
  for _ in range(10):
    CI.update([])


@pytest.mark.parametrize('fw_case', ['known_old_firmware', 'eps_only', 'unknown_engine', 'missing'])
@pytest.mark.parametrize('alpha_long', [False, True])
def test_auto_firmware_and_vin_paths_keep_the_real_chassis(fw_case, alpha_long):
  car_fw = _firmware(fw_case)
  _, matches = match_fw_to_car(car_fw, VIN_2021, log=False)
  assert matches == {str(CAR.MAZDA_CX5)}
  _assert_personal(_params(next(iter(matches)), car_fw, alpha_long), alpha_long)
