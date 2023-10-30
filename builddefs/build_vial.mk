# Copyright 2023 Ilya Zhuravlev
# SPDX-License-Identifier: GPL-2.0-or-later

QMK_SETTINGS ?= yes
TAP_DANCE_ENABLE ?= yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    OPT_DEFS += -DTAPPING_TERM_PER_KEY
endif
COMBO_ENABLE ?= yes
KEY_OVERRIDE_ENABLE ?= yes
SRC += $(QUANTUM_DIR)/vial.c
OPT_DEFS += -DVIAL_ENABLE -DNO_DEBUG -DSERIAL_NUMBER=\"vial:f64c2b3c\"

ifeq ($(strip $(VIAL_INSECURE)), yes)
    OPT_DEFS += -DVIAL_INSECURE
endif

ifeq ($(strip $(VIALRGB_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/vialrgb.c
    OPT_DEFS += -DVIALRGB_ENABLE
endif

ifeq ($(strip $(QMK_SETTINGS)), yes)
    AUTO_SHIFT_ENABLE := yes
    SRC += $(QUANTUM_DIR)/qmk_settings.c
    OPT_DEFS += -DQMK_SETTINGS \
        -DAUTO_SHIFT_NO_SETUP -DAUTO_SHIFT_REPEAT_PER_KEY -DAUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY \
        -DPERMISSIVE_HOLD_PER_KEY -DHOLD_ON_OTHER_KEY_PRESS_PER_KEY -DTAPPING_FORCE_HOLD_PER_KEY -DRETRO_TAPPING_PER_KEY \
        -DCOMBO_TERM_PER_COMBO
endif

# Generate Vial layout definition header from JSON
$(QUANTUM_DIR)/vial.c: $(INTERMEDIATE_OUTPUT)/src/vial_generated_keyboard_definition.h

$(INTERMEDIATE_OUTPUT)/src/vial_generated_keyboard_definition.h: $(KEYMAP_PATH)/vial.json
	python3 util/vial_generate_definition.py $(KEYMAP_PATH)/vial.json $(INTERMEDIATE_OUTPUT)/src/vial_generated_keyboard_definition.h
