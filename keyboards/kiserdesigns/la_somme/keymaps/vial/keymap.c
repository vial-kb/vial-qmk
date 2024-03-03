 /* This program is free software: you can redistribute it and/or modify
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

#define KC_NUM_SPC LT(1, KC_SPC)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_GSCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,     KC_P,
    KC_GA,   KC_AS,   KC_CD,   KC_SF,   KC_G,    KC_H,    KC_SJ,    KC_CK,   KC_AL,    KC_ENT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,     KC_M,    KC_COMM,  KC_DOT,
            KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, KC_NUM_SPC, KC_RALT, KC_RGUI, KC_RCTL,        KC_ESC
  ),
  [1] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS,
    KC_LCBR, KC_LBRC, KC_LPRN, KC_UNDS, KC_NO,   KC_RPRN, KC_RBRC, KC_RCBR, KC_SCLN, KC_QUOTE,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [1] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()){
        HSV layer_hsv = {rgb_matrix_get_hue(), ((int)rgb_matrix_get_sat()>>1)+128, rgb_matrix_get_val()}; //get the matrix hue, sat (minimum 50%), and value
        HSV mod_hsv = {rgb_matrix_get_hue(), ((int)rgb_matrix_get_sat()>>1)+128, rgb_matrix_get_val()};

        layer_hsv.h += 16*get_highest_layer(layer_state|default_layer_state); //hue-shift the layer indicator based on highest layer (of 0-15 layers)
        layer_hsv.h = layer_hsv.h % 256; //modulo 256

        int mods = get_mods() | get_oneshot_mods(); //get all modifiers, either held or OSM
        mods = ((mods>>4)|mods) & 0x0F;  //combine left and right mods, and take just the bottom 4 bits (0-15)

        mod_hsv.h += 16*mods; //hue-shift the modifier indicator based on the modifiers held (of 0-15 combinations)
        mod_hsv.h = mod_hsv.h % 256; //modulo 256

        if (host_keyboard_led_state().caps_lock) { //if capslock is active
            layer_hsv.s = 0; //turn both indicators white
            mod_hsv.s = 0;
        };

        RGB layer_rgb = hsv_to_rgb(layer_hsv);
        RGB mod_rgb = hsv_to_rgb(mod_hsv);
        rgb_matrix_set_color(0, layer_rgb.r, layer_rgb.g, layer_rgb.b);
        rgb_matrix_set_color(1, mod_rgb.r, mod_rgb.g, mod_rgb.b);
    }
	return true;
}
