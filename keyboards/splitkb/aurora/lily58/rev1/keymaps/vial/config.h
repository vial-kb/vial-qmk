#pragma once

#define VIAL_KEYBOARD_UID {0x0B, 0x9F, 0x90, 0x91, 0x81, 0x04, 0x83, 0xB1}
/* Vial secure unlock - currently using both big keys, like with base lily58 */
#define VIAL_UNLOCK_COMBO_ROWS {4, 9}
#define VIAL_UNLOCK_COMBO_COLS {5, 5}

/* saving some more space, */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
