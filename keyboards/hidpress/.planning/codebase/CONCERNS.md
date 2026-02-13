# Codebase Concerns

**Analysis Date:** 2026-02-13

## Tech Debt

**Direct I2C Display Initialization Workaround:**
- Issue: `bipedalambi.c:5-12` sends SSD1306 display off command directly via raw I2C transmission before the OLED driver initializes. This is a workaround to prevent OLED initialization issues on split keyboards.
- Files: `bipedalambi/bipedalambi.c`
- Impact: Fragile initialization sequence dependent on I2C timing. If QMK OLED driver initialization changes, this workaround may break. Hardware-specific hardcoded I2C address (0x3C).
- Fix approach: Move to proper QMK OLED pre-initialization hooks or investigate the root cause of OLED driver conflicts with split keyboard communication.

**Hardcoded Joystick ADC Pins Without Abstraction:**
- Issue: Joystick ADC pins are hardcoded in matrix_scan_user (GP28, GP29 for left; GP26, GP27 for southpaw) with magic number 512 for center calibration
- Files: `bipedalambi/keymaps/vial_left/keymap.c:228-229`, `bipedalsouthpaw/keymaps/vial/keymap.c:285-319`
- Impact: No abstraction layer for joystick configuration. Changes to hardware pins require code modifications. No calibration mechanism - assumes 10-bit ADC with exact center at 512.
- Fix approach: Create joystick abstraction layer with configurable pins and calibration offsets stored in EEPROM.

**Actuation Level Management Duplication:**
- Issue: Each keyboard variant (bipedalambi left/right, bipedalsouthpaw) duplicates identical EEPROM save/load logic and actuation arrays
- Files: `bipedalambi/keymaps/vial_left/keymap.c:64-90`, `bipedalambi/keymaps/vial_right/keymap.c:52-78`, `bipedalsouthpaw/keymaps/vial/keymap.c`
- Impact: Maintenance burden - changes to actuation logic require updates in multiple places. Risk of inconsistency between implementations.
- Fix approach: Extract EEPROM and actuation logic into shared header file or common keyboard library.

**Global State Variables for Split Keyboard Synchronization:**
- Issue: `current_mode` and `actuation` are declared as `extern` in `.h` files and defined globally. Split keyboard halves share these via shared data mechanism, but state updates are not synchronized atomically.
- Files: `bipedalambi/bipedalambi.h:15-18`, `bipedalambi/keymaps/vial_left/keymap.c:44-47`, `bipedalsouthpaw/bipedalsouthpaw_shared.h:14-21`
- Impact: On split keyboards, pressing actuation keys on one side while the other side is processing may cause state inconsistency. Layer mode changes could miss synchronization.
- Fix approach: Use QMK's transaction-based split sync mechanism with explicit sync points after state modifications.

## Known Bugs

**OLED Display Flickering on Layer/Mode Changes:**
- Symptoms: Display clears multiple times when changing layers or toggling actuation display
- Files: `bipedalambi/bipedalambi.c:515-533`, `bipedalsouthpaw/bipedalsouthpaw.c:550-573`
- Trigger: Pressing layer keys or actuation adjustment keys causes repeated `oled_clear()` calls from both mode display logic and state update logic
- Workaround: None currently - inherent to current architecture where multiple state handlers call clear independently

**ADC Value Aliasing Between Joystick Axes:**
- Symptoms: Joystick drift or phantom keypresses when moving diagonally
- Files: `bipedalambi/keymaps/vial_left/keymap.c:224-274`
- Trigger: Reading both X and Y axes in same matrix_scan cycle without per-axis latching. If one axis crosses threshold while other is being read, state can become inconsistent
- Workaround: Move joystick very slowly or press keys manually instead of using joystick custom keys mode

**Uninitialized Customkeys Array on Split Half Startup:**
- Symptoms: Right side of bipedalambi may register phantom joystick key presses at startup
- Files: `bipedalambi/keymaps/vial_left/keymap.c:57` (not defined on right side)
- Trigger: Right half (vial_right) does not have joystick mode, but if custom keys logic ever runs there, `customkeys[]` array is not initialized
- Workaround: Restart keyboard or press reset button

## Performance Bottlenecks

**Warp Particle Screensaver: O(N²) Pixel Drawing on OLED Task:**
- Problem: Screensaver animation renders all particles every frame with multiple pixel writes per particle
- Files: `bipedalambi/bipedalambi.c:315-351` (50 particles, 3+ pixels each per frame every 40ms)
- Cause: `render_warp()` iterates all particles and writes 3 trail pixels + optional glow pixels (5 more). No spatial optimization or dirty rectangle tracking.
- Improvement path: Implement framebuffer-based rendering or limit particle count based on display update frequency. Cache previous frame for erase-before-redraw.

**Noise Fill During OLED Startup: O(width*height) Per Frame:**
- Problem: `fill_noise()` generates sparse random noise by checking every pixel - 4096 random checks per 50ms frame during 1-second startup
- Files: `bipedalambi/bipedalambi.c:372-385`
- Cause: No pre-generated noise pattern, checking every pixel individually
- Improvement path: Pre-generate 1-2 noise patterns at initialization, cycle through them instead of recalculating.

**ADC Polling Every Matrix Scan Without Debouncing:**
- Problem: Joystick ADC values read on every matrix_scan (likely 10ms-25ms intervals) without averaging or debouncing
- Files: `bipedalambi/keymaps/vial_left/keymap.c:228-229`
- Cause: Direct read and comparison against static thresholds with no hysteresis
- Improvement path: Implement rolling average buffer (3-5 samples) and add hysteresis window (±50 around threshold).

## Fragile Areas

**OLED Task User Complex State Machine:**
- Files: `bipedalambi/bipedalambi.c:432-536`
- Why fragile: 5 overlapping concerns in single 100+ line function: startup animation, screensaver, activity detection, screen off timer, and normal display. Nested if-else with multiple state variables (`oled_startup_complete`, `screensaver_active`, `screen_is_off`, `showing_actuation`, `was_showing_actuation`).
- Safe modification: Extract screensaver into separate function with clear entry/exit conditions. Create state enum instead of multiple bools.
- Test coverage: No tests for startup animation fade timing, screensaver timeout ordering, or mode transitions.

**Dynamic Keymap Joystick Integration:**
- Files: `bipedalambi/keymaps/vial_left/keymap.c:224-274`
- Why fragile: Reads keycodes from dynamic keymap at runtime in matrix_scan. If dynamic keymap write occurs mid-scan, values could be corrupted. No validation of returned keycodes.
- Safe modification: Cache keycode reads at layer_state change, not during scan. Validate keycode range before use.
- Test coverage: No integration tests for dynamic keymap + joystick interaction.

**I2C Dual Bus Configuration for Split Displays:**
- Files: `bipedalambi/mcuconf.h:5-11`, `bipedalambi/keymaps/vial_left/config.h:18-24`, `bipedalambi/keymaps/vial_right/config.h`
- Why fragile: Left and right halves use different I2C buses (I2C0 and I2C1) with identical pin names but different GPIO mappings. Swapping firmware between sides would cause I2C address conflicts.
- Safe modification: Add validation in firmware to detect if running on wrong half and display error message.
- Test coverage: No tests for firmware flashed to wrong half.

## Test Coverage Gaps

**No Coverage for Screensaver State Transitions:**
- What's not tested: Verify screensaver activates after 60 seconds, screen off after 300 seconds, proper exit on activity
- Files: `bipedalambi/bipedalambi.c:486-507`
- Risk: Screensaver timer resets could get lost with matrix changes, leaving screen on indefinitely
- Priority: High

**No Coverage for Joystick Mode Switching with Active Presses:**
- What's not tested: Switching from MODE_CUSTOM_KEYS to MODE_MOUSE mid-press (while joystick is deflected)
- Files: `bipedalambi/keymaps/vial_left/keymap.c:157-163`, `bipedalambi/keymaps/vial_left/keymap.c:224-274`
- Risk: Stuck key registers if mode changes while joystick is over actuation threshold
- Priority: High

**No Coverage for EEPROM Persistence Edge Cases:**
- What's not tested: Invalid data in EEPROM (all 0xFF), partial writes interrupted, corruption recovery
- Files: `bipedalambi/keymaps/vial_left/keymap.c:77-90` (load_layer_config_from_eeprom)
- Risk: Corrupted EEPROM could cause layer modes to not load, using undefined values
- Priority: Medium

**No Coverage for Split Keyboard State Sync:**
- What's not tested: Layer mode changes propagate correctly between halves, actuation index stays synchronized
- Files: `bipedalambi/bipedalambi.c:122`, `bipedalambi/keymaps/vial_left/keymap.c:160-161`
- Risk: Layer modes could diverge between halves in extreme cases (simultaneous layer key press + mode change)
- Priority: Medium

**No Coverage for Dynamic Keymap Corruption Handling:**
- What's not tested: What happens if dynamic_keymap_get_keycode returns invalid value (0x0000, 0xFFFF)
- Files: `bipedalambi/keymaps/vial_left/keymap.c:234, 245, 256, 267`
- Risk: Invalid keycodes could cause undefined behavior in handle_joystick_keycode
- Priority: Medium

## Security Considerations

**No Input Validation on Dynamic Keymap Keycodes:**
- Risk: Malicious Vial configuration could write out-of-range keycodes that cause buffer overflows
- Files: `bipedalambi/keymaps/vial_left/keymap.c:234-271` (dynamic_keymap_get_keycode result used directly)
- Current mitigation: QMK's dynamic keymap layer is assumed safe; no validation in firmware
- Recommendations: Add bounds checking and keycode validation before using in handle_joystick_keycode. Validate against KC_A through KC_SLSH + QK_KB_0 through QK_KB_31.

**I2C Display Control Without Authentication:**
- Risk: Malicious device on I2C bus could send display off command and lock user out
- Files: `bipedalambi/bipedalambi.c:12` (i2c_transmit with hardcoded address)
- Current mitigation: Physical access required to reach I2C bus
- Recommendations: Document that untrusted I2C devices should not be connected during use.

## Dependencies at Risk

**QMK OLED Driver Dependency - Version Mismatch Risk:**
- Risk: OLED initialization workaround in `keyboard_pre_init_user` assumes SSD1306 and specific initialization order
- Impact: QMK OLED refactors could break initialization sequence
- Migration plan: Monitor QMK updates for OLED driver changes. Create feature flag for legacy OLED init if needed.

**Analog Joystick ADC Support - Driver Implementation Dependency:**
- Risk: Analog joystick functionality depends on `analogReadPin()` from QMK analog driver
- Impact: Changes to analog driver ADC resolution handling (8-bit vs 10-bit) would break calibration
- Migration plan: Document assumption of 10-bit ADC. Add runtime detection of ADC resolution.

## Missing Critical Features

**No Actuation Hysteresis Implementation:**
- Problem: Joystick actuation uses direct threshold comparison without hysteresis, causing jitter at boundary
- Blocks: Reliable joystick operation in noisy environments, dead zone customization
- Recommendation: Implement hysteresis window (±threshold_range) before registering press/release.

**No Joystick Calibration Storage:**
- Problem: Joystick assumes hardcoded center at 512 (10-bit ADC midpoint), no way to recalibrate for hardware variation
- Blocks: Users cannot adjust joystick sensitivity per-unit, drift correction
- Recommendation: Add calibration routine callable from Vial, store min/max/center in EEPROM.

**No Error Recovery for I2C Communication Failures:**
- Problem: If I2C display goes offline, firmware has no fallback display mechanism and continues using OLED commands
- Blocks: Graceful degradation when display hardware fails
- Recommendation: Add I2C error detection in oled_task_user, display status on LED or disable rendering.

---

*Concerns audit: 2026-02-13*
