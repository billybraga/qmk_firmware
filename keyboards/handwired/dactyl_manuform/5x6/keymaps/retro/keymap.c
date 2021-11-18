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
