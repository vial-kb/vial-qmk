# External Integrations

**Analysis Date:** 2026-02-13

## APIs & External Services

**None detected** - This is firmware code with no external API integrations. The keyboard communicates only with:
- Host computer via USB HID (Human Interface Device) protocol
- Local peripherals via I2C, SPI, and GPIO

## Data Storage

**Databases:**
- Not applicable - No database used. Runtime configuration stored in:
  - Vial EEPROM - Dynamic keymap configuration stored in microcontroller flash memory via Vial protocol
  - QMK EEPROM - Persistent settings (RGB state, encoder preferences) in microcontroller flash

**File Storage:**
- Not applicable - Firmware is self-contained. No external file system or cloud storage

**Caching:**
- None - Real-time processing only

## Authentication & Identity

**Auth Provider:**
- Custom - None required. USB device authenticated by host OS via:
  - Vendor ID (VID): 0xD812 (HIDPRESS custom)
  - Product ID (PID): Model-specific (0x0020 for Bipedal65, 0x0021 for Bipedal Ambi)
  - USB HID descriptors

**Implementation:**
- USB HID standard implementation via QMK
- Vial unlock combo - Optional two-key combination defined in keymap for Vial configuration access
  - Example in `bipedalambi/info.json`: keys at matrix [0,0] and [0,1]

## Monitoring & Observability

**Error Tracking:**
- None - Embedded firmware with no remote telemetry

**Logs:**
- OLED display output - Real-time rendering of:
  - Current layer state (text and bitmap graphics)
  - Pointing device mode (mouse, scroll, keycodes) via `render_layer_state()` in `bipedalsouthpaw.c`
  - Actuation level indicator for analog switches
  - Startup animation (warp particle effect)
  - Screensaver animation after 60 seconds inactivity (warp particles)
  - Screen power-off after 5 minutes (configurable via `SCREEN_OFF_TIMEOUT`)

**Debug:**
- Console feature disabled in all keyboards (`"console": false` in `info.json`)
- Command feature disabled (`"command": false`)
- Optional serial debug via USART (not configured)

## CI/CD & Deployment

**Hosting:**
- Not applicable - Deployed directly to RP2040 via USB bootloader

**Build System:**
- Local QMK build via `make hidpress/[keyboard]:vial` or `make hidpress/[keyboard]:via`
- Two keymap variants per keyboard:
  - `via` - VIA configurability (older protocol)
  - `vial` - Vial configurability (newer, more flexible)
  - `default` - Static configuration only (bipedalambi only)

**Bootloader:**
- RP2040 native USB bootloader (not customizable)
- Double-tap reset enters bootloader mode (200ms timeout configurable via `RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT`)

## Environment Configuration

**Required env vars:**
- Not applicable - Firmware is configured entirely through:
  - Header files (`config.h`, `halconf.h`, `mcuconf.h`)
  - `info.json` definitions
  - Build-time `rules.mk` feature flags

**Configuration Methods:**
1. **Compile-time** - Modified `config.h` and `rules.mk`, rebuild firmware
2. **Runtime** - Via Vial GUI application (keymaps only, features require rebuild)

**Secrets location:**
- Not applicable - No credentials or API keys required

## Webhooks & Callbacks

**Incoming:**
- None - Keyboard only receives USB HID protocol data from host

**Outgoing:**
- HID reports - Standard USB Human Interface Device reports sent to host:
  - Keyboard reports (key matrix scans)
  - Mouse/pointing device reports (X/Y coordinates, buttons)
  - Consumer control reports (media keys, brightness)

## USB Protocol Details

**Device Class:**
- USB Composite Device:
  - Keyboard interface (HID)
  - Optional Mouse interface (when pointing device enabled)
  - Optional Joystick interface (bipedalambi only)

**Communication:**
- Full-speed USB 2.0 (12 Mbps)
- Interrupt transfers for HID reports
- USB bus-powered with optional self-power support

**USB IDs (per keyboard):**
- Bipedal65: VID=0xD812, PID=0x0020, device_version=0.0.1
- Bipedal Southpaw: VID=0xD812, PID=0x0020, device_version=0.0.1
- Bipedal Ambi: VID=0xD812, PID=0x0021, device_version=0.0.1

## Communication Protocols

**Split Keyboard (Bipedalambi only):**
- Serial USART full-duplex communication between left and right halves
- Data synchronized:
  - Matrix state from both sides
  - Layer state (split layer state enabled)
  - Pointing device position and clicks
- Protocol: QMK serial protocol (custom binary format)

**OLED Display (all keyboards):**
- I2C protocol
- Address: 0x3C (0x78 in 8-bit format)
- Speed: Standard (100kHz) or Fast (400kHz)
- Display: SSD1306 128x32 monochrome
- Pre-initialization: Display powered off until ready to prevent garbage data

**RGB LEDs (Bipedal65, Bipedal Southpaw):**
- SPI-like communication via RP2040 PIO (Programmable IO) blocks
- WS2812B protocol (NeoPixel)
- Animation support built into QMK rgblight module

**Analog Joystick (Bipedal Ambi, Bipedal Southpaw):**
- ADC (Analog-to-Digital Converter) input
- X axis: GP29 (Ambi left), GP22 (Southpaw)
- Y axis: GP28 (Ambi left), GP23 (Southpaw)
- Auto-axis configuration enabled
- Dead zone cutoff enabled
- Speed regulator set to 20 for smooth movement
- Pointing device mode: left-side control only (split pointing enabled)

## Hardware Integration Points

**Encoder Input:**
- GPIO interrupt-based
- Per-keyboard mappings in keymaps via `ENCODER_MAP_ENABLE`
- Three encoders typically supported per layout

**Button Matrix:**
- Diode-per-switch (column-to-row) topology
- COL2ROW scanning direction
- Bootmagic support (hold key during power-on for special modes)
- NKRO (n-key rollover) enabled for all-key presses

---

*Integration audit: 2026-02-13*
