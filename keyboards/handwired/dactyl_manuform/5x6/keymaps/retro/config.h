/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define USE_SERIAL
#define MASTER_LEFT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define TAPPING_TOGGLE 2
#define RETRO_TAPPING
#define RETRO_TAPPING_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS
#define COMBO_VARIABLE_LEN
// #define COMBO_TERM 50
// #define TAPPING_TERM 200
#define ABBR_TERM 500
#define MUTE_LEFT_DESKTOP LT(0, KC_M)
#define ANSWER_RIGHT_DESKTOP LT(0, KC_A)
#define LEFT_PREV LT(0, KC_L)
#define RIGHT_NEXT LT(0, KC_N)
