#include QMK_KEYBOARD_H

enum retro_layers {
    _QWERTY, // 0
    _BEPO, // 1
    _R_THUM_2_4, // 2
    _L_THUM_3_4, // 3
    _THUMBS, // 4
    _CTL_ENT, // 5
    _L_THUMB2, // 6
    _L2_THUMB, // 7
    _R2_THUMB, // 8
    _L_THUMB_R_KB, // 9
    _NOLAN, // 10
    _BEPO_SFT, // 11
    _SFT_ARROWS, // 12
    _ARROWS, // 13
    _STENO // 14
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
    CTL_ENT_5,
    PIPE,
    QWERTY,
    BEPO,
    R_THUM_2_4,
    L_THUM_3_4,
    L_THUMB2,
    L2_THUMB,
    R2_THUMB,
    L_THUMB_R_KB,
    NOLAN,
    BEPO_SFT_11_12,
    BEPO_SFT_R_THUMB_11,
    SFT_ARROWS,
    ARROWS,
    LALT_TICK,
    GO_FILE,
    LEFT_PREV,
    RIGHT_NEXT,
    PLAY_STOP
};

#include "sendstring_canadian_multilingual.h"
#include "g/keymap_combo.h"
#include "retro_keymap.c"

void no_ctrl(keyrecord_t *record, uint16_t code1, uint16_t code2) {
    bool is_ctrl = get_mods() & MOD_BIT(KC_LCTL);
    if (is_ctrl) {
        unregister_code(KC_LCTL);
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
    if (is_ctrl) {
        register_code(KC_LCTL);
    }
}

void no_ctrl1(keyrecord_t *record, uint16_t code1) {
    no_ctrl(record, code1, 0);
}

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
    static uint16_t CTL_ENT_timer;
    static bool CTL_ENT_is_last_pressed;
    static bool CTL_ENT_registered_ctl;
    static uint16_t BEPO_SFT_R_THUMB_timer;
    static bool BEPO_SFT_R_THUMB_is_last_pressed;
    static uint16_t LEFT_PREV_timer;
    static uint16_t RIGHT_NEXT_timer;
    static uint16_t PLAY_STOP_timer;

    if (record->event.pressed) {
        CTL_ENT_is_last_pressed = keycode == CTL_ENT_5;
        BEPO_SFT_R_THUMB_is_last_pressed = keycode == BEPO_SFT_R_THUMB_11;
    }

    if (record->event.pressed && IS_LAYER_ON(_STENO) && keycode == R_THUM_2_4) {
        layer_off(_STENO);
        return false;
    }

    switch (keycode) {
        case LEFT_PREV:
            if (record->event.pressed) {
                LEFT_PREV_timer = timer_read();
            } else {
                if (timer_elapsed(LEFT_PREV_timer) < TAPPING_TERM) {
                    tap_code(KC_LEFT);
                } else {
                    tap_code_delay(KC_MPRV, 50);
                }
            }
            return false;
        case RIGHT_NEXT:
            if (record->event.pressed) {
                RIGHT_NEXT_timer = timer_read();
            } else {
                if (timer_elapsed(RIGHT_NEXT_timer) < TAPPING_TERM) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code_delay(KC_MNXT, 50);
                }
            }
            return false;
        case PLAY_STOP:
            if (record->event.pressed) {
                PLAY_STOP_timer = timer_read();
            } else {
                if (timer_elapsed(PLAY_STOP_timer) < TAPPING_TERM) {
                    tap_code(KC_MPLY);
                } else {
                    tap_code(KC_MSTP);
                }
            }
            return false;
        case LALT_TICK:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(0xC0);
            } else {
                unregister_code(KC_LALT);
            }
            return false;
        case CTL_ENT_5:
            if (record->event.pressed) {
                if (CTL_ENT_is_last_pressed && timer_elapsed(CTL_ENT_timer) < TAPPING_TERM) {
                    // CTL_ENT was the last pressed (and released), and was pressed two times in TAPPING_TERM
                    register_code(KC_ENT);
                } else {
                    // We registered the ctrl if it was not already
                    CTL_ENT_registered_ctl = !(get_mods() & MOD_BIT(KC_LCTL));
                    
                    register_code(KC_LCTL);
                    layer_on(_CTL_ENT);
                }
                
                CTL_ENT_timer = timer_read();
            } else {
                if (CTL_ENT_registered_ctl) {
                    // Only unregister if we are the one that registered it
                    unregister_code(KC_LCTL);
                }
                layer_off(_CTL_ENT);

                if (CTL_ENT_is_last_pressed && timer_elapsed(CTL_ENT_timer) < TAPPING_TERM) {
                    tap_code(KC_ENT);
                }
            }
            return false;
        case BEPO_SFT_11_12:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                layer_on(_BEPO_SFT);
            } else {
                unregister_code(KC_LSFT);
                layer_off(_BEPO_SFT);
            }
            return false;
        case BEPO_SFT_R_THUMB_11: // + z
            if (record->event.pressed) {
                BEPO_SFT_R_THUMB_timer = timer_read();
                register_code(KC_LSFT);
                layer_on(_BEPO_SFT);
            } else {
                unregister_code(KC_LSFT);
                layer_off(_BEPO_SFT);

                if (BEPO_SFT_R_THUMB_is_last_pressed && timer_elapsed(BEPO_SFT_R_THUMB_timer) < TAPPING_TERM) {
                    tap_code(KC_Z);
                }
            }
            return false;
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

        case GO_FILE:
            if (record->event.pressed) {
                // ctrl+shift+space
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);

                // ctrl+V
                register_code(KC_LCTL);
                register_code(KC_V);
                unregister_code(KC_V);
                unregister_code(KC_LCTL);

                // ctrl+left
                register_code(KC_LCTL);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                unregister_code(KC_LCTL);

                // ctrl+backspace
                register_code(KC_LCTL);
                register_code(KC_BSPC);
                unregister_code(KC_BSPC);
                unregister_code(KC_LCTL);

                _delay_ms(250);

                // enter
                register_code(KC_ENT);
                unregister_code(KC_ENT);
            }
            break;

        // layers
        case R_THUM_2_4:
            if (record->event.pressed) {
                layer_on(_R_THUM_2_4);
            } else {
                layer_off(_R_THUM_2_4);
            }
            return false;
            break;
        case L_THUM_3_4:
            if (record->event.pressed) {
                layer_on(_L_THUM_3_4);
            } else {
                layer_off(_L_THUM_3_4);
            }
            return false;
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _R_THUM_2_4, _L_THUM_3_4, _THUMBS);
  state = update_tri_layer_state(state, _R_THUM_2_4, _BEPO_SFT, _SFT_ARROWS);
  return state;
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BEPO_SFT_R_THUMB_11:
            return true;
        default:
            return false;
    }
}
