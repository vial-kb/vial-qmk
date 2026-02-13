# Phase 1: Reference Analysis - Context

**Gathered:** 2026-02-13
**Status:** Ready for planning

<domain>
## Phase Boundary

Cross-reference the Sofle rev1 Vial split keyboard configuration as a known-working baseline for how split matrix conventions work in vial-qmk. Establish what the correct row-doubling, vial.json structure, and encoder mapping look like so subsequent phases can apply the fix with confidence.

</domain>

<decisions>
## Implementation Decisions

### What "correct" looks like
- Layer 0 = full keymap, layers 1-3 = KC_TRNS except specific overrides (standard QMK pattern)
- 4 layers required (DYNAMIC_KEYMAP_LAYER_COUNT=4)
- Both layer mapping AND persistence are equally important to verify
- Both halves must show up correctly in Vial independently (each half is configured separately via USB)

### Split architecture model
- Each half builds and flashes separately: `make hidpress/bipedalambi:vial_left` and `:vial_right`
- Each half has its own vial.json: `keymaps/vial_left/vial.json` and `keymaps/vial_right/vial.json`
- When plugged into USB, Vial only shows keys for the connected half (not full keyboard)
- Either half can be USB master — no fixed master side
- This means the MATRIX_ROWS doubling convention may work differently than single-binary split boards — the reference analysis must determine whether each independent half should use doubled rows or per-side rows

### Sofle as reference
- Written fresh using Sofle rev1 Vial keymap AND the Bipedal Southpaw macropad as dual references
- Matrix dimensions between Sofle and Ambi are not known to match — need side-by-side comparison
- Key count difference unknown — need to count
- Sofle Vial config is assumed working (from upstream vial-qmk repo) but not personally tested
- The reference analysis should extract the specific conventions Sofle uses, not blindly copy its values

### Peripheral preservation (CRITICAL CONSTRAINT)
- Thumbstick (left half) and encoder (right half, uses ENCODER_MAP_ENABLE for Vial control) are working correctly
- Thumbstick directions are configurable in Vial (mapped to matrix positions)
- **DO NOT break**: OLED display, layer state display, actuation level system, actuation value display, screensaver animation, joystick modes, encoder functionality
- These features are existing and working — the fix must preserve them, not modify them
- Any vial.json changes must maintain existing thumbstick and encoder matrix positions

### Claude's Discretion
- How to structure the reference comparison document (table, narrative, etc.)
- Which specific Sofle files to prioritize reading
- Level of detail in the "what Ambi must also do" checklist

</decisions>

<specifics>
## Specific Ideas

- The Bipedal Southpaw macropad (`keyboards/hidpress/bipedalsouthpaw/`) is also a valid reference for how custom features (actuation, scroll direction EEPROM) work in isolation
- Left half has thumbstick only (no encoder), right half has encoder only (no thumbstick)
- The independent-half-per-firmware model may mean Sofle's approach to row doubling differs from what Ambi needs — this is the key question Phase 1 must answer

</specifics>

<deferred>
## Deferred Ideas

None — discussion stayed within phase scope

</deferred>

---

*Phase: 01-reference-analysis*
*Context gathered: 2026-02-13*
