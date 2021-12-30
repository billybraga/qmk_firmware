#include QMK_KEYBOARD_H

enum retro_keys {
  E_TREM = SAFE_RANGE,
  U_GRAVE,
  E_TREM_UPPER,
  U_GRAVE_UPPER,
  E_ACUTE,
  ARR,
  L_ARR,
  TICK_KEY,
  TILDE,
  HAT,
  SEM_COL,
  CTL_ENT
};

#include "retro_keymap.c"
#include "sendstring_canadian_multilingual.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_ENT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                layer_on(5);
            } else {
                layer_off(5);
                unregister_code(KC_LCTL);
            }
            break;
        case MO(11):
            if (record->event.pressed) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            break;
        case SEM_COL:
            if (record->event.pressed) {
                send_unicode_string(";");
            }
            break;
        case E_ACUTE:
            if (record->event.pressed) {
                send_string("é");
            }
            break;
        case E_TREM:
            if (record->event.pressed) {
                send_unicode_string("ë");
            }
            break;
        case U_GRAVE:
            if (record->event.pressed) {
                send_unicode_string("ù");
            }
            break;
        case E_TREM_UPPER:
            if (record->event.pressed) {
                send_unicode_string("Ë");
            }
            break;
        case U_GRAVE_UPPER:
            if (record->event.pressed) {
                send_unicode_string("Ù");
            }
            break;
        case ARR:
            if (record->event.pressed) {
                send_string(" => ");
            }
            break;
        case L_ARR:
            if (record->event.pressed) {
                send_string("x => ");
            }
            break;
        case TICK_KEY:
            if (record->event.pressed) {
                send_unicode_string("`");
            }
            break;
        case TILDE:
            if (record->event.pressed) {
                send_unicode_string("~");
            }
            break;
        case HAT:
            if (record->event.pressed) {
                send_unicode_string("^");
            }
            break;
        case KC_F22:
            if (record->event.pressed) {
                send_string("qu'on ");
            }
            break;
        case KC_F23:
            if (record->event.pressed) {
                send_string("que ");
            }
            break;
        case KC_F24:
            if (record->event.pressed) {
                send_string("est-ce ");
            }
            break;
        }
    return true;
};
