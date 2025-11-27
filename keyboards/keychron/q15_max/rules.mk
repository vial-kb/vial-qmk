# Q15 Max specific build rules for Vial branch
# Wireless features are not available in Vial branch

# Add Keychron common source directly (no .mk file in Vial branch)
VPATH += keyboards/keychron/common
SRC += keychron_common.c

# Use simplified q15_max_vial.c instead of q15_max.c (which has wireless deps)
SRC += keyboards/keychron/q15_max/q15_max_vial.c
