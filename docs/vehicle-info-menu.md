# Vehicle info menu

A read-only menu that shows what the car already broadcasts on CAN but openpilot has no
control-path use for: coolant temperature, engaged transmission gear, door and lamp states,
blind-spot status. Car generic: a platform declares its rows, everything downstream is shared.

## Shape

```
opendbc/sunnypilot/car/vehicle_info_base.py       VehicleInfoItem + the VehicleInfo runtime
opendbc/sunnypilot/car/vehicle_info.py            brand registry + the UI-side label lookup
opendbc/sunnypilot/car/mazda/vehicle_info.py      the mazda_2017 declaration
selfdrive/car/card.py                             owns it, feeds it CAN, publishes at 2 Hz
cereal/custom.capnp                               VehicleInfoSP (was CustomReserved10)
selfdrive/ui/sunnypilot/lib/vehicle_info.py       rows + formatting, shared by both families
selfdrive/ui/sunnypilot/mici/layouts/vehicle.py   MICI: settings -> vehicle
selfdrive/ui/sunnypilot/layouts/settings/vehicle/ TICI: appended to the Vehicle panel
```

A row is one DBC signal:

```python
VehicleInfoItem("coolantTemp", "coolant temp", "CHECK_AND_TEMP", "COOLANT_TEMP",
                group=ItemGroup.powertrain, unit=Unit.celsius)
```

`scale`/`offset` are applied on top of the DBC's own factor, and are for presentation only -- a
signal whose DBC *decode* is wrong gets fixed in the DBC, so every consumer benefits. `unit` has
to be one the UI knows how to localize; add a member alongside the item that needs it.
`type` picks the rendering: `number`, `flag` (on/off), or `state` (labelled from the item's own
map, else the DBC's `VAL_` table).

Adding a brand is one entry in `VEHICLE_INFO_ITEMS` plus a `get_<brand>_items(CP, CP_SP)`. A
brand with no entry gets an empty menu and pays nothing: no parser is built, no values published.

## Why it parses into its own CANParser

Reading the car's existing parsers would have been free, and is wrong. `CANParser` registers a
message once, with the strictness of whichever caller got there first, and vehicle info has to
relax the liveness, checksum and counter checks so that a signal this particular car does not
broadcast reads as unavailable instead of invalidating the whole bus. Registering first would
have silently applied that relaxation to messages `carState` depends on. `CANParser` grew
`ignore_checksum`/`ignore_counter` constructor flags for this; they default off.

Measured: with the shared-parser version, `carState.canValid` on a CX-5 segment differed from the
baseline (22 invalid startup frames vs 16). With a separate parser it is identical frame for
frame, which is the property the tests in
`opendbc/sunnypilot/car/tests/test_vehicle_info.py::TestVehicleInfoIsolation` lock down.

`card` owns the object and feeds it, exactly as it does `RadarInterface` -- a peer consumer of
the same CAN drain rather than something bolted into the car interface. Nothing in opendbc's
control path knows this feature exists, so nothing declared here can fault a drive.

## Mazda (mazda_2017 DBC)

34 rows, every one read back out of the rlog corpus in `tools/mazda_long/` before being listed.
The interesting findings:

| signal | finding |
|---|---|
| `CHECK_AND_TEMP.COOLANT_TEMP` | raw byte with the usual -40 C bias, which the DBC was missing. 93..130 raw = 53..90 C across the corpus, and the coldest cold start is 55 raw = 15 C. **Fixed in `mazda_2017.dbc`** |
| `CHECK_AND_TEMP.OUTDOOR_TEMP` | **the DBC offset was wrong.** Decoded as `raw * 0.25 - 63` everything sits near -40 C. Drop the offset and the corpus spans 7.0 C in March to 38.0 C in July, monthly minima track the season, and the coldest cold start lands just above that month's coldest ambient. `raw * 0.5 - 40` would put March at -26 C. **Fixed in `mazda_2017.dbc`**, evidence recorded on the `CM_ SG_` lines |
| `GEAR.GEAR_BOX` | the engaged gear, not a status code: 1 below 10 kph, 2 at 10-19, 3 at 20-29, 5 at 50-59, 6 above 70. 14 appears exactly when the selector is in R, 0 covers park and neutral |
| `EPB.EPB_ACTIVE` | never 1 while moving in 196k samples. Genuine parking brake, and `carState.parkingBrake` is unset on Mazda today |
| `BRAKE.BRAKE_PRESSURE` | rests at 152 counts for 99.8% of unbraked samples and climbs to ~190 under braking. Counts, not calibrated pressure, so shown as a delta off 152 |
| `CHECK_AND_TEMP.CHARGING_SYSTEM_MALFUNCTION` | asserts for 97% of engine-off samples and 0.01% with the engine running: the alternator lamp |

### Left out, and why

Warning lamps that never asserted anywhere in the corpus are still listed. An unlit lamp is the
expected reading, and a wrong bit position costs a lamp that stays dark, not a false alarm. What
is left out is either indistinguishable from a wake-up state or unexplained:

| signal | measurement |
|---|---|
| `TRACTION.ABS_MALFUNCTION` / `TCS_DCS_MALFUNCTION` | 2-bit, not flags. Sit at 2 and 3 for 67% of engine-off samples and still appear with the engine running (0.15%), so "not ready" cannot be told from "faulted" |
| `STEER_RATE.HANDS_OFF_5_SECONDS` | on for 32% of engine-running samples, far too often for the warning its name suggests |
| `STEER_RATE.LKAS_TRACK_STATE` | on for 98% of engine-off samples and 24% while running |
| `BRAKE.VEHICLE_ACC_X` / `ACC_Y` | -0.88 m/s^2 bias at a standstill, and ACC_Y parks on 4.092 (the top of its range) often enough to look like a sentinel |
| `ENGINE_DATA.PEDAL_GAS` | 12 bits, seen up to 900, no scale that lands it on 0-100% |
| `TEMPERATURE.*` | flat 0 across the whole corpus |
| `HVAC.*` | signals are unnamed in the DBC |

## Cost

Nothing, unless the menu is on screen.

The UI half is free by construction: `gui_app.render()` only drives the top one or two nav-stack
widgets, and `_update_state()` is only reachable through `render()`, so a closed panel does no
work at all. Cars whose brand declares no items are free too -- no parser is built and the
publish is skipped.

The card half is a second CAN pass, so it is gated: the panel sets `VehicleInfoActive` on show
and clears it on hide, and card checks that flag on the publish tick and skips both the parse and
the publish when it is unset. A panel that misses its hide event (a UI crash) leaves card parsing
until the next boot, which is where it started -- `CLEAR_ON_MANAGER_START` handles the rest.
`vehicleInfoSP` is deliberately not logged: nothing but this menu consumes it.

Measured on a replayed CX-5 segment (5246 frames/s, card at 100 Hz):

| | ms per 10 ms card cycle |
|---|---|
| the car's own parsers | 0.083 |
| the vehicle-info parser, menu open | 0.017 |
| the vehicle-info parser, menu closed | 0 |

With the menu open that is +20% on `CI.update()`, or 1.7 ms per second of driving. The parser is
built with `record_all=False` -- vehicle info only ever reads `vl`, and not maintaining `vl_all`
(104 `list.clear()` per update plus an append per decode) is worth 26% of the pass. Opening the
menu populates every row within ~230 ms.

Decimating the parse instead of gating it would **not** work: `valid` keys on a 2 s window, so
parsing 1 cycle in 5 gives the 2.1 Hz `DOORS` message a 59% chance of a sample and all six door
rows would flicker.

## Known gaps

- Item labels are not translatable. They live in the platform declaration in opendbc, which
  cannot import the UI, so `tr()` sees a variable and the extractor never finds them. Group names
  are marked with `tr_noop` and do get extracted.
- `EPB.EPB_ACTIVE` looks like it should feed `carState.parkingBrake`, which Mazda leaves unset.
  Out of scope here, worth a follow-up.
- `VehicleInfo.update()` measures staleness against the last packet its parser saw, so a parser
  that has stopped being fed reports its last readings as fresh. card gates the feed and the
  publish together so nothing stale is ever published, but anything else calling it has to keep
  feeding it.
