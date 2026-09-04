# Private CX-5 configuration

This branch is exclusively for the owner's **2021 Mazda CX-5 with a confirmed 2022 CX-5 EPS swap**. It is not a stock-CX-5 or general-purpose vehicle release.

- Select the **2017–21 CX-5** entry for this 2021 car. Do not select the 2022–25 CX-5 entry; it is not an alias for this configuration.
- The personal configuration retains the 2021 chassis identity, mass, wheelbase, steering ratio and tire stiffness. The existing 2022-EPS steering delay, torque limits and driver-torque protections are retained.
- The hardware configuration is explicit. Missing/unknown engine firmware or an incomplete EPS query does not change Alpha availability or no-warning behavior. This assumes the owner's confirmed swap; **do not install on an original pre-2022 EPS or another vehicle**.
- Alpha Longitudinal remains optional through the existing toggle. When disabled at initialization, openpilot longitudinal control and the Mazda longitudinal safety flag are off. Existing stock-radar handback/restart logic is unchanged.
- No-warning suppresses the generic cluster hands-on/steer-required request only. The comma display and real steering-fault handling remain; temporary steering faults can still request the cluster warning.
- No power-management, Wi-Fi, UI, longitudinal actuation limits, radar-session logic, or safety-hook code is changed by this personal-profile patch.

Software tests are not real-car validation. After updating while parked, verify the selected profile and Alpha-off stock ACC recovery before relying on a changed configuration. This patch does not establish radar/brake compatibility solely from the EPS swap.
