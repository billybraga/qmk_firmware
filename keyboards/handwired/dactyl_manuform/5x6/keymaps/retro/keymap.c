#include QMK_KEYBOARD_H
#include "retro_keymap.c"
#include "sendstring_canadian_multilingual.h"

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
                SEND_STRING(" => ");
            }
            break;
        case KC_F18:
            if (record->event.pressed) {
                SEND_STRING("x => ");
            }
            break;
        case KC_F19:
            if (record->event.pressed) {
                send_unicode_string("`");
            }
            break;
        }
    return true;
};
