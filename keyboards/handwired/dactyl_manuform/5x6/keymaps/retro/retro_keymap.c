#include QMK_KEYBOARD_H

/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_RBRC), KC_GRV, KC_NUBS, KC_NUHS, KC_EQL, MO(2), LCTL_T(KC_ENT), KC_SPC, MO(1), MO(5), KC_LALT, KC_BSPC, KC_RALT, KC_LGUI, MO(8), KC_RGUI, MO(7)),
	[1] = LAYOUT_5x6(KC_TILD, KC_EXLM, RALT(KC_2), KC_HASH, KC_DLR, KC_PERC, LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), KC_TRNS, KC_TRNS, KC_BTN2, KC_MS_U, KC_BTN1, KC_NO, KC_RBRC, KC_PGUP, KC_UP, KC_PGDN, KC_NO, KC_RBRC, KC_TRNS, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_RSFT, KC_TRNS, KC_TRNS, KC_WH_U, KC_MS_D, KC_WH_D, KC_NO, KC_BSPC, KC_HOME, KC_DOWN, KC_END, KC_DEL, KC_ENT, KC_LCBR, KC_RCBR, KC_TRNS, KC_P0, MO(3), KC_TRNS, MO(7), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_5x6(KC_PSCR, KC_MRWD, LALT(KC_N), KC_MPLY, KC_VOLD, KC_VOLU, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, LCTL(KC_F12), KC_BSPC, KC_DEL, KC_F10, KC_F11, LSFT(KC_F11), KC_PMNS, KC_P4, KC_P5, KC_P6, KC_F17, KC_F18, LCTL(KC_F12), LCTL(KC_BSPC), LSFT(KC_DEL), LCA(KC_ENT), KC_SPC, LCTL(KC_F5), KC_APP, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_P0, KC_PDOT, KC_TRNS, MO(6), RCS(KC_SPC), MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TT(9), KC_TRNS),
	[3] = LAYOUT_5x6(KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, LCTL(KC_PGUP), LGUI(KC_UP), LCTL(KC_PGDN), KC_NO, KC_NO, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LCTL(LGUI(KC_LEFT)), LGUI(KC_DOWN), LCTL(LGUI(KC_RGHT)), LGUI(KC_RGHT), KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, LGUI(KC_PGUP), KC_NO, LGUI(KC_PGDN), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_F17, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[4] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_H), KC_NO, KC_NO, LCTL(KC_L), KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[5] = LAYOUT_5x6(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[6] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_F4), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_SPC), KC_NO, KC_NO, KC_NO, RCS(KC_R), RCS(KC_T), KC_NO, KC_NO, RCS(KC_I), RCS(KC_O), KC_NO, KC_NO, LSFT(KC_DEL), RCS(KC_A), RCS(KC_S), KC_NO, RCS(KC_F), RCS(KC_G), RCS(KC_H), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_SPC), KC_NO, KC_NO, RCS(KC_C), RCS(KC_V), RCS(KC_B), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LGUI(KC_SPC), KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[7] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TAB, KC_Q, KC_W, KC_W, KC_E, KC_R, KC_NO, RCS(KC_PGUP), RCS(KC_UP), RCS(KC_PGDN), KC_NO, KC_NO, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, RCS(KC_LEFT), RCS(KC_DOWN), RCS(KC_RGHT), KC_NO, KC_NO, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, RCS(KC_DOWN), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_ENT), KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS),
	[8] = LAYOUT_5x6(KC_MINS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_Y, KC_U, KC_I, KC_P, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NO, LCTL(LGUI(KC_LEFT)), KC_NO, LCTL(LGUI(KC_RGHT)), KC_NO, KC_NO, KC_LCTL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO),
	[9] = LAYOUT_5x6(TO(0), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_GRV, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SCLN, KC_GRV, KC_QUOT, KC_NO, KC_BSLS, KC_EQL, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_LEFT, KC_NO, KC_RGHT, KC_NO, KC_NO, KC_TRNS, KC_DOWN)
};

