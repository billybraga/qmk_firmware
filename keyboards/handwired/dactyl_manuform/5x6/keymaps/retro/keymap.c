#include QMK_KEYBOARD_H
#include "retro_keymap.c"

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_NUBS):
            return false;
        default:
             return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_F17:
        if (record->event.pressed) {
            // when keycode MACRO_ARROW is pressed
            SEND_STRING(" => ");
        } else {
            // when keycode MACRO_ARROW is released
        }
        break;
    case KC_F18:
        if (record->event.pressed) {
            // when keycode MACRO_ARROW is pressed
            SEND_STRING("x => ");
        } else {
            // when keycode MACRO_ARROW is released
        }
        break;
    case KC_F19:
        if (record->event.pressed) {
            SEND_STRING("#");
        }
        break;
    }
    return true;
};
