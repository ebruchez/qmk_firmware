#include QMK_KEYBOARD_H

#define _MAIN 0
#define _INTELLIJ_DEBUG 1
#define _CURSOR 2
#define _LIGHTS 3
/*#define _INTELLIJ_MISC 2
#define _MEDIA 3*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_2x4(
     TO(_INTELLIJ_DEBUG), KC_BRIGHTNESS_UP,   KC__MUTE,            KC__VOLUP,
     KC_NO,               KC_BRIGHTNESS_DOWN, KC_MEDIA_PLAY_PAUSE, KC__VOLDOWN
  ),
  [_INTELLIJ_DEBUG] = LAYOUT_ortho_2x4(
    TO(_CURSOR), KC_F9,  C(KC_F10), C(LCMD(KC_F5)),
    KC_F5,       KC_F11, S(KC_F11), KC_F10
  ),
  [_CURSOR] = LAYOUT_ortho_2x4(
    TO(_LIGHTS), KC_UP,   KC_HOME,  KC_PGUP,  
    KC_LEFT,     KC_DOWN, KC_RIGHT, KC_PGDOWN
  ),
  [_LIGHTS] = LAYOUT_ortho_2x4(
     TO(_MAIN),        BL_STEP,          BL_BRTG,        BL_TOGG,          
     RGB_MODE_FORWARD, RGB_MODE_RAINBOW, RGB_MODE_SNAKE, RGB_TOG
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // oled_write_ln_P(PSTR("Erik's Macro Pad"), true);
  oled_write_P(PSTR("Mode: "), false);

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      oled_write_ln_P(PSTR("Main"), true);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("MODE Bri+ Mute Vol+ "), false);
      oled_write_ln_P(PSTR("     Bri- Play Vol- "), false);
      break;
    case _INTELLIJ_DEBUG:
      oled_write_ln_P(PSTR("Debug"), true);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("MODE Brpt Crsr Cont "), false);
      oled_write_ln_P(PSTR("Cnct Into Out  Over "), false);
      break;
    case _CURSOR:
      oled_write_ln_P(PSTR("Cursor"), true);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("MODE Up   Home PgUp"), false);
      oled_write_ln_P(PSTR("Left Down Righ PgDn"), false);
      break;
    case _LIGHTS:
      oled_write_ln_P(PSTR("Lights"), true);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("MODE Step Brth BL  "), false);
      oled_write_ln_P(PSTR("Mode Rain Snak RGB "), false);
      break;
    default:
      oled_write_ln_P(PSTR("N/A"), true);
  }

#ifdef RGBLIGHT_ENABLE
/*
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
*/
#endif

  return false;
}
#endif
