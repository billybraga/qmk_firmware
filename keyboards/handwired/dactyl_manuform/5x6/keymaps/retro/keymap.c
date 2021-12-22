#include QMK_KEYBOARD_H

enum retro_keys {
  E_TREM = SAFE_RANGE,
  U_GRAVE,
  E_TREM_UPPER,
  U_GRAVE_UPPER
};

#include "retro_keymap.c"
#include "sendstring_canadian_multilingual.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case E_TREM:
            if (record->event.pressed) {
                send_unicode_string("ë");
            }
            break;
        case KC_F14:
            if (record->event.pressed) {
                send_unicode_string("ù");
            }
            break;
        case KC_F15:
            if (record->event.pressed) {
                send_unicode_string("Ë");
            }
            break;
        case KC_F16:
            if (record->event.pressed) {
                send_unicode_string("Ù");
            }
            break;
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
        case KC_F20:
            if (record->event.pressed) {
                send_unicode_string("~");
            }
            break;
        case KC_F21:
            if (record->event.pressed) {
                send_unicode_string("^");
            }
            break;
        case KC_F22:
            if (record->event.pressed) {
                send_unicode_string("qu'on ");
            }
            break;
        case KC_F23:
            if (record->event.pressed) {
                send_unicode_string("que ");
            }
            break;
        case KC_F24:
            if (record->event.pressed) {
                send_unicode_string("est-ce ");
            }
            break;
        }
    return true;
};
