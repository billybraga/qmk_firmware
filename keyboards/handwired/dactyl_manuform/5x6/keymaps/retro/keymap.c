#include QMK_KEYBOARD_H

/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT), KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_BSLS), KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, MO(2), LCTL_T(KC_ENT), KC_SPC, TT(1), TT(5), KC_LALT, KC_BSPC, TT(7), MO(8), KC_LGUI, KC_LGUI, KC_RCTL),
	[1] = LAYOUT_5x6(KC_TILD, KC_EXLM, RALT(KC_2), KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL, KC_TRNS, KC_TRNS, KC_BTN2, KC_MS_U, KC_BTN1, KC_NO, KC_RBRC, KC_PGUP, KC_UP, KC_PGDN, KC_NO, KC_RBRC, KC_TRNS, KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_BSLS, KC_TRNS, KC_TRNS, KC_WH_U, KC_MS_D, KC_WH_D, KC_NO, KC_BSPC, KC_HOME, KC_DOWN, KC_END, KC_DEL, KC_UNDS, KC_LCBR, KC_RCBR, KC_TRNS, KC_P0, MO(3), KC_TRNS, MO(7), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_5x6(KC_PSCR, KC_MRWD, KC_MFFD, KC_MPLY, KC_VOLD, KC_VOLU, KC_MSTP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, LCTL(KC_F12), KC_BSPC, KC_DEL, KC_F10, KC_F11, KC_F5, KC_RPRN, KC_LALT, KC_MPLY, KC_MNXT, KC_TRNS, KC_RSFT, LCTL(KC_F12), LCTL(KC_BSPC), LSFT(KC_DEL), KC_NO, KC_SPC, LCTL(KC_F5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_LT, KC_GT, KC_TRNS, MO(6), RCS(KC_SPC), MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_R), RCS(KC_T), KC_NO, LCTL(KC_PGUP), LCTL(KC_UP), LCTL(KC_PGDN), KC_NO, KC_NO, KC_LSFT, RCS(KC_A), LSFT(KC_DEL), KC_NO, RCS(KC_F), KC_NO, KC_NO, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_RGHT), RCS(KC_SPC), KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_C), RCS(KC_V), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[4] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_H), KC_NO, KC_NO, LCTL(KC_L), KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[5] = LAYOUT_5x6(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[6] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_SPC), KC_NO, KC_NO, KC_NO, RCS(KC_R), RCS(KC_T), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_DEL), RCS(KC_A), RCS(KC_S), KC_NO, RCS(KC_F), RCS(KC_G), RCS(KC_H), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RCS(KC_SPC), KC_NO, KC_NO, RCS(KC_C), RCS(KC_V), RCS(KC_B), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[7] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TAB, KC_Q, KC_W, KC_W, KC_E, KC_R, KC_NO, RCS(KC_PGUP), RCS(KC_UP), RCS(KC_PGDN), KC_NO, KC_NO, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, RCS(KC_LEFT), RCS(KC_DOWN), RCS(KC_RGHT), KC_NO, KC_NO, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, RCS(KC_DOWN), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_ENT), KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO),
	[8] = LAYOUT_5x6(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_P, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCTL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO)
};

