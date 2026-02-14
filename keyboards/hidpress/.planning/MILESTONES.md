# Milestones

## v1.0 EEPROM / Vial Layer Fix (Shipped: 2026-02-14)

**Phases completed:** 8 phases, 10 plans
**Timeline:** 2026-02-13 to 2026-02-14 (2 days)

**Delivered:** Fixed the Vial layer offset bug on the Bipedal Ambi split keyboard — keycodes now persist correctly and layers display without offset in the Vial GUI.

**Key accomplishments:**
- Fixed vial.json matrix rows (4 to 8) in both halves to match config.h MATRIX_ROWS
- Remapped right-half KLE positions for standalone operation (rows 0-3, not 4-7)
- Fixed NUM_ENCODERS split-doubling (set to 1 explicitly)
- Verified EEPROM budget: 568 bytes / 4096 bytes (13.9%) — no collisions
- Added eeconfig_init_user for safe EEPROM clear defaults on both halves
- Added EE_CLR keycode to both keymaps for easy EEPROM clearing
- Compiled, flashed, and verified both halves working in Vial

**Archive:** `milestones/v1.0-ROADMAP.md`, `milestones/v1.0-REQUIREMENTS.md`

---
