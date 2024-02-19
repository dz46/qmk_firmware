/*
Copyright 2021 andys8 <andys8@users.noreply.github.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum custom_keycodes {
    VOICE_TOGGLE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(G(KC_D),            KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,
               KC_B,               KC_H,                   KC_I ,
               VOICE_TOGGLE,       KC_F23,                 KC_F24),
};


bool dc_voice = true;
bool ts_voice = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
           case KC_F23:
                dc_voice = !dc_voice;
                break; 
            case KC_F24:
                ts_voice = !ts_voice;
                break;
            case VOICE_TOGGLE:
                dc_voice = !dc_voice;
                tap_code(KC_F23);
                ts_voice = !ts_voice;
                tap_code(KC_F24);
                break;
        }
    } 

    return true;
};



void set_led_voice_dc(void) {
    if(dc_voice == true) {
        rgb_matrix_set_color(7, RGB_GREEN);
    } else {
        rgb_matrix_set_color(7, RGB_RED);
    }
}

void set_led_voice_ts(void) {
    if(ts_voice == true) {
        rgb_matrix_set_color(6, RGB_GREEN);
    } else {
        rgb_matrix_set_color(6, RGB_RED);
    }
}

void set_led_voice(void) {
    if(dc_voice == true && ts_voice == true) {
        rgb_matrix_set_color(8, RGB_GREEN);
        return;
    }
    
    if(dc_voice == false && ts_voice == false) {
        rgb_matrix_set_color(8, RGB_RED);
        return;
    }
        rgb_matrix_set_color(8, RGB_CORAL);
}


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    set_led_voice_dc();
    set_led_voice_ts();
    set_led_voice();

    return true;
}


void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_GOLD);

    // Default colors for Voice
    rgb_matrix_set_color(6, RGB_GREEN);
    rgb_matrix_set_color(7, RGB_GREEN);
    rgb_matrix_set_color(8, RGB_GREEN);
}

