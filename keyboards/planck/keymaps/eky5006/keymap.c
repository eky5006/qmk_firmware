/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

// For Alt Tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum planck_layers {
  _QWERTY,
  _QWERTY2,
  _NUMPAD,
  _HRGN,
  _HRGN2,
  _LOWER,
  _RAISE,
  _ADJUST,
  _UTILITY,
  _EXTRA
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY2,
  NUMPAD,
  HRGN,
  HRGN2,
  UTILITY,
  LTEM,
  S1, S2, S3, S4, S5, S6
};

// Tap Dance declarations
enum {
    SFT_CAPS,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define UTILITY MO(_UTILITY)
#define HRGN2 MO(_HRGN2)
#define LTEM LT(_EXTRA,KC_MUTE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Mute |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Esc  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TD(SC)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |RS/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |UTLTY | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    LTEM,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ESC,
    KC_TAB,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TD(SFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
    UTILITY,      KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Qwerty2
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |RS/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY2] = LAYOUT_planck_grid(
    KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
    KC_LCTL,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * | Mute |      |  Up  |      |      |      |      |  7   |  8   |  9   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  | Left | Down |Right |      |      |      |  4   |  5   |  6   |  *   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |      |      |  1   |  2   |  3   |  -   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |UTLTY | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise |  0   |  .   |  +   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    _______, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,    XXXXXXX,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, XXXXXXX,
    XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,    KC_KP_ENTER,
    _______, _______, _______, _______, _______, KC_BSPC, KC_SPC,  _______, KC_KP_0, KC_KP_DOT, KC_KP_PLUS,   XXXXXXX
),

/* Hiragana - just for funsies
 * ,-----------------------------------------------------------------------------------.
 * |      |  た  |  て  |  い  |  す   |  か  |  ん  |  な  |  に   |  ら  |  せ  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  ち  |  と  |  し  |  は   |  き  |  く  |  ま  |  の   |  り  |  れ  |  け  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  つ  |  さ  |  そ  |  ひ   |  こ  |  み  |  も  |  ね   |  る  |  め  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HRGN] = LAYOUT_planck_grid(
    _______, UC(0x305F), UC(0x3066), UC(0x3044), UC(0x3059), UC(0x304B), UC(0x3093), UC(0x306A), UC(0x306B), UC(0x3089), UC(0x305B), _______,
    _______, UC(0x3061), UC(0x3068), UC(0x3057), UC(0x306F), UC(0x304D), UC(0x304F), UC(0x307E), UC(0x306E), UC(0x308A), UC(0x308C), UC(0x3051),
    HRGN2,   UC(0x3064), UC(0x3055), UC(0x305D), UC(0x3072), UC(0x3053), UC(0x307F), UC(0x3082), UC(0x306D), UC(0x308B), UC(0x3081), _______,
    _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),


/* Hiragana 2nd layer - just for funsies
 * ,-----------------------------------------------------------------------------------.
 * |      |  た  |  て  |  い  |  す   |  か  |  ん  |  な  |  に   |  ら  |  せ  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HRGN2] = LAYOUT_planck_grid(
    _______, UC(0x306C), UC(0x3075), UC(0x3042), UC(0x3046), UC(0x3048), UC(0x304A), UC(0x3084), UC(0x3086), UC(0x3088), UC(0x308F), UC(0x307B),
    _______, UC(0x308D), _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | PSCR | SLCK | Home | End  | PAUS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Stop | Play | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_HOME, KC_END,  KC_PAUS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   `  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | NLCK |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Stop | Play | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_NLCK, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |HueTgl| Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|QWRTY2|NUMPAD| HRGN |UC_MOD|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    C(A(KC_LBRC)), RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______,       _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  QWERTY2,  NUMPAD,  HRGN,    UC_MOD,
    _______,       MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* Utility
 * ,-----------------------------------------------------------------------------------.
 * |CK_TOG|  S1  |  S2  |  S3  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  S4  |  S5  |  S6  |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |CtlBks|      |      | Prev | Stop | Play | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_UTILITY] = LAYOUT_planck_grid(
    CK_TOGG, S1,      S2,      S3,      XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, S4,      S5,      S6,      XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(KC_BSPC), XXXXXXX, XXXXXXX, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
),

/* Extra
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EXTRA] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Left Shift, twice for Caps Lock
    [SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float qwerty_song[][2]     = SONG(QWERTY_SOUND);
  float colemak_song[][2]    = SONG(COLEMAK_SOUND);
  float dvorak_song[][2]     = SONG(DVORAK_SOUND);
  float s1[][2]              = SONG(MARIO_MUSHROOM);
  float s2[][2]              = SONG(EYES_ON_ME);
  float s3[][2]              = SONG(FF_PRELUDE2X);
  float s4[][2]              = SONG(SW_VADER);
  float s5[][2]              = SONG(TERRAS_THEME);
  float s6[][2]              = SONG(VICTORY_FANFARE_SHORT);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(qwerty_song);
        #endif
        layer_move(_QWERTY);
      }
      return false;
      break;
    case QWERTY2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(colemak_song);
        #endif
        layer_move(_QWERTY2);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(dvorak_song);
        #endif
        layer_move(_NUMPAD);
      }
      return false;
      break;
    case HRGN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(plover_song);
        #endif
        layer_move(_HRGN);
      }
      return false;
      break;
    case S1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s1);
        #endif
      }
      return false;
      break;
    case S2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s2);
        #endif
      }
      return false;
      break;
    case S3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s3);
        #endif
      }
      return false;
      break;
    case S4:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s4);
        #endif
      }
      return false;
      break;
    case S5:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s5);
        #endif
      }
      return false;
      break;
    case S6:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(s6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (IS_LAYER_ON(_EXTRA)) {
    if (clockwise) { // Custom Global hotkeys for Hue lights
      tap_code16(C(A(KC_RCBR)));
    } else {
      tap_code16(C(A(KC_LCBR)));
    }
  } else if (IS_LAYER_ON(_LOWER)) {
    if (clockwise) { // Global hotkeys for Flux
      tap_code16(LALT(KC_PGUP));
    } else {
      tap_code16(LALT(KC_PGDN));
    }
  } else if (IS_LAYER_ON(_UTILITY)) {
    if (clockwise) { // Web browser tab cycling
      tap_code16(LCTL(KC_PGDN));
    } else {
      tap_code16(LCTL(KC_PGUP));
    }
  } else if (IS_LAYER_ON(_RAISE)) {
    if (clockwise) { // Alt Tab
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      tap_code16(KC_TAB);
    } else {
      alt_tab_timer = timer_read();
      tap_code16(S(KC_TAB));
    }
  } else {
    if (clockwise) { // Volume control
      tap_code(KC_AUDIO_VOL_UP);
    } else {
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
          #ifdef AUDIO_ENABLE
            static bool play_sound = false;
          #endif
            if (active) {
              #ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
              #endif
                layer_on(_ADJUST);
            } else {
              #ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
              #endif
                layer_off(_ADJUST);
            }
          #ifdef AUDIO_ENABLE
            play_sound = true;
          #endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

// For Alt Tab. Release Alt if tab hasn't been sent in a second. 
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
