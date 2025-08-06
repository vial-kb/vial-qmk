#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    #define AUDIO_INIT_DELAY
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2
#define VIAL_KEYBOARD_UID {0xAF, 0x13, 0x31, 0x67, 0xE5, 0xBC, 0x4E, 0xF6}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }
