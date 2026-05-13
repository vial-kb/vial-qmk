# Sofle Choc Maltron-B — rules.mk
# Pro Micro RP2040 build target

# Convert this build for Pro Micro RP2040
CONVERT_TO          = promicro_rp2040

# Split keyboard
SPLIT_KEYBOARD      = yes

# RGB matrix (per-key WS2812 LEDs)
RGB_MATRIX_ENABLE   = yes
RGB_MATRIX_DRIVER   = ws2812

# Combos for the 37 chord definitions
COMBO_ENABLE        = yes

# OLED display (SSD1306, 128x32, rotated to 32x128)
OLED_ENABLE         = yes
OLED_DRIVER         = ssd1306

# Rotary encoder with per-layer mapping
ENCODER_ENABLE      = yes
ENCODER_MAP_ENABLE  = yes

# Misc features
EXTRAKEY_ENABLE     = yes
MOUSEKEY_ENABLE     = yes
NKRO_ENABLE         = yes
LTO_ENABLE          = yes

# WPM tracking — required for OLED WPM display
WPM_ENABLE          = yes

# ─── DISABLED FEATURES ───────────────────────────────────
# Tap dance was removed during debugging — re-enable only if needed
TAP_DANCE_ENABLE    = no

# Vial / Via — explicitly disabled. The vial-qmk fork may still try to
# compile vial.c if these are not set. Both lines required.
VIA_ENABLE          = no
VIAL_ENABLE         = no
