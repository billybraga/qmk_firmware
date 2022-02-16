#include QMK_KEYBOARD_H

enum retro_layers {
  _QWERTY,
  _BEPO,
  _R_THUMB,
  _L_THUMB,
  _THUMBS,
  _CTRL_HK,
  _L_THUMB2,
  _L2_THUMB,
  _R2_THUMB,
  _L_THUMB_R_KB,
  _NOLAN,
  _BEPO_SFT,
  _BEPO_SFT_R_THUMB,
  _ARROWS
};

enum retro_keys {
  E_TREM = SAFE_RANGE,
  U_GRAVE,
  E_ACUTE,
  L_ARR1,
  L_ARR2,
  TICK_KEY,
  TILDE,
  HAT,
  SEM_COL,
  CTL_ENT,
  PIPE,
  QWERTY,
  BEPO,
  R_THUMB,
  L_THUMB,
  CTRL_HK,
  L_THUMB2,
  L2_THUMB,
  R2_THUMB,
  L_THUMB_R_KB,
  NOLAN,
  BEPO_SFT,
  BEPO_SFT_R_THUMB,
  ARROWS
};

#include "retro_keymap.c"
#include "sendstring_canadian_multilingual.h"

void no_sft(keyrecord_t *record, uint16_t code1, uint16_t code2) {
    bool is_sft = get_mods() & MOD_BIT(KC_LSFT);
    if (is_sft) {
        unregister_code(KC_LSFT);
    }
    if (record->event.pressed) {
        register_code(code1);
        if (code2 != 0) {
            register_code(code2);
        }
    } else {
        unregister_code(code1);
        if (code2 != 0) {
            unregister_code(code2);
        }
    }
    if (is_sft) {
        register_code(KC_LSFT);
    }
}

void no_sft1(keyrecord_t *record, uint16_t code1) {
    no_sft(record, code1, 0);
}

void alt_gr(keyrecord_t *record, uint16_t new_code) {
    no_sft(record, KC_RALT, new_code);
}

void lsft(keyrecord_t *record, uint16_t new_code) {
    if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(new_code);
    } else {
        unregister_code(new_code);
        unregister_code(KC_LSFT);
    }
}

void alt_gr_then(keyrecord_t *record, uint16_t new_code, uint16_t after_code) {
    alt_gr(record, new_code);
    if (!record->event.pressed) {
        register_code(after_code);
        unregister_code(after_code);
    }
}

void alt_gr_dead(keyrecord_t *record, uint16_t new_code) {
    alt_gr_then(record, new_code, KC_SPC);
}

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
//         case LT(11, KC_W):
            if (record->event.pressed) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            break;
        case SEM_COL:
            no_sft1(record, KC_SCLN);
            break;
        case E_ACUTE:
            if (record->event.pressed) {
                register_code(KC_SLSH);
            } else {
                unregister_code(KC_SLSH);
            }
            break;
        case E_TREM:
            lsft(record, KC_LBRC);
            break;
        case U_GRAVE:
            alt_gr_then(record, KC_LBRC, KC_U);
            break;
        case L_ARR1:
            if (record->event.pressed) {
                send_string("x => x.");
            }
            break;
        case L_ARR2:
            if (record->event.pressed) {
                send_string("() => ");
            }
            break;
        case TICK_KEY:
            alt_gr_dead(record, KC_LBRC);
            break;
        case TILDE:
            alt_gr_dead(record, KC_RBRC);
            break;
        case HAT:
            if (record->event.pressed) {
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LBRC);
            }
            break;
        case PIPE:
            alt_gr(record, KC_GRV);
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

        // layers
        case R_THUMB:
            if (record->event.pressed) {
                layer_on(_R_THUMB);
                update_tri_layer(_R_THUMB, _L_THUMB, _THUMBS);
            } else {
                layer_off(_R_THUMB);
                update_tri_layer(_R_THUMB, _L_THUMB, (int) _THUMBS);
            }
            return false;
            break;
        case L_THUMB:
            if (record->event.pressed) {
                layer_on(_L_THUMB);
                update_tri_layer(_R_THUMB, _L_THUMB, (int) _THUMBS);
            } else {
                layer_off(_L_THUMB);
                update_tri_layer(_R_THUMB, _L_THUMB, (int) _THUMBS);
            }
            return false;
            break;
    }
    return true;
};
