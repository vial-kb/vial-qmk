VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
VIALRGB_ENABLE = yes

# Use eager debouncing for faster response time
# The RP2040 has plenty of processing power to handle eager debouncing,
# which provides better responsiveness for gaming by immediately registering
# key presses while only debouncing the key release.
DEBOUNCE_TYPE = sym_eager_pk