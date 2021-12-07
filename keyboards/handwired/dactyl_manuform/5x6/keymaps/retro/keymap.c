#include QMK_KEYBOARD_H
#include "retro_keymap.c"

enum custom_keycodes {
    MACRO_ARROW = KC_F17,
};

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
    case MACRO_ARROW:
        if (record->event.pressed) {
            // when keycode MACRO_ARROW is pressed
            SEND_STRING("=>");
        } else {
            // when keycode MACRO_ARROW is released
        }
        break;
    }
    return true;
};
