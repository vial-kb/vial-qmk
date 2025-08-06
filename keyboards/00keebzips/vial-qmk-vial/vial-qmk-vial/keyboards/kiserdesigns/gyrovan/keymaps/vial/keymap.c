/* Copyright 2024 Noah Kiser (NCKiser)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                                 KC_MUTE,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  KC_SPC,  KC_SPC,           KC_APP,  KC_RALT, KC_RGUI, KC_RCTL
    )
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_HOME, KC_END) }
    };
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()){
        HSV layer_hsv = {rgb_matrix_get_hue(), ((int)rgb_matrix_get_sat()>>1)+128, rgb_matrix_get_val()}; //get the matrix hue, sat (minimum 50%), and value
        HSV lock_hsv = {(rgb_matrix_get_hue()+(rgb_matrix_get_speed()>>1))%256, ((int)rgb_matrix_get_sat()>>1)+128, 0};
        HSV mod_hsv = {(rgb_matrix_get_hue()+2*(rgb_matrix_get_speed()>>1))%256, ((int)rgb_matrix_get_sat()>>1)+128, 0};

        layer_hsv.h += 32*get_highest_layer(layer_state|default_layer_state); //hue-shift the layer indicator based on highest layer (of 0-7 layers)
        layer_hsv.h = layer_hsv.h % 256; //modulo 256

        int mods = get_mods() | get_oneshot_mods(); //get all modifiers, either held or OSM
        //0bGASC
        mods = ((mods>>4)|mods) & 0x0F;  //combine left and right mods, and take just the bottom 4 bits (0-15)
        if (mods == 0b0001){mod_hsv.h = ( mod_hsv.h + 0 )%256;   mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0011){mod_hsv.h = ( mod_hsv.h + 32 )%256;  mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0010){mod_hsv.h = ( mod_hsv.h + 64 )%256;  mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0110){mod_hsv.h = ( mod_hsv.h + 96 )%256;  mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0100){mod_hsv.h = ( mod_hsv.h + 128 )%256; mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1100){mod_hsv.h = ( mod_hsv.h + 160 )%256; mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1000){mod_hsv.h = ( mod_hsv.h + 192 )%256; mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1001){mod_hsv.h = ( mod_hsv.h + 224 )%256; mod_hsv.s = mod_hsv.s;      mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1010){mod_hsv.h = ( mod_hsv.h + 85 )%256;  mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0101){mod_hsv.h = ( mod_hsv.h + 213 )%256; mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1110){mod_hsv.h = ( mod_hsv.h + 128 )%256; mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b0111){mod_hsv.h = ( mod_hsv.h + 43 )%256;  mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1011){mod_hsv.h = ( mod_hsv.h + 0 )%256;   mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1101){mod_hsv.h = ( mod_hsv.h + 171 )%256; mod_hsv.s = mod_hsv.s >> 1; mod_hsv.v = rgb_matrix_get_val();}
        if (mods == 0b1111){mod_hsv.h = mod_hsv.h;               mod_hsv.s = 0;              mod_hsv.v = rgb_matrix_get_val();}

        int locks = (host_keyboard_led_state().caps_lock << 0) | ( (1-host_keyboard_led_state().num_lock) << 1) | (host_keyboard_led_state().scroll_lock << 2);
        //0bSNC
        if (locks == 0b001){lock_hsv.h = ( lock_hsv.h + 0 )%256;   lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b010){lock_hsv.h = ( lock_hsv.h + 85 )%256;  lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b100){lock_hsv.h = ( lock_hsv.h + 171 )%256; lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b011){lock_hsv.h = ( lock_hsv.h + 43 )%256;  lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b110){lock_hsv.h = ( lock_hsv.h + 128 )%256; lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b101){lock_hsv.h = ( lock_hsv.h + 213 )%256; lock_hsv.s = lock_hsv.s;      lock_hsv.v = rgb_matrix_get_val();}
        if (locks == 0b111){lock_hsv.h = lock_hsv.h;               lock_hsv.s = lock_hsv.s >> 1; lock_hsv.v = rgb_matrix_get_val();}

        RGB layer_rgb = hsv_to_rgb(layer_hsv);
        RGB lock_rgb = hsv_to_rgb(lock_hsv);
        RGB mod_rgb = hsv_to_rgb(mod_hsv);
        int top_row = via_get_layout_options()&0x80 ? 0 : 1;
        rgb_matrix_set_color(0 + 3*top_row, layer_rgb.r, layer_rgb.g, layer_rgb.b);
        rgb_matrix_set_color(1 + 3*top_row, lock_rgb.r, lock_rgb.g, lock_rgb.b);
        rgb_matrix_set_color(2 + 3*top_row, mod_rgb.r, mod_rgb.g, mod_rgb.b);
        rgb_matrix_set_color(3 - 3*top_row, 0, 0, 0);
        rgb_matrix_set_color(4 - 3*top_row, 0, 0, 0);
        rgb_matrix_set_color(5 - 3*top_row, 0, 0, 0);
    }
	return true;
}
