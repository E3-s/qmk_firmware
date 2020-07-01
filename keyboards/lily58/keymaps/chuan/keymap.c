#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

bool is_ctrl_tab_active = false;
bool is_alt_tab_active = false;
bool is_alt_left_active = false;
bool is_alt_right_active = false;
bool is_sft_down_active = false;
bool is_sft_left_active = false;
bool is_sft_right_active = false;
bool is_sft_up_active = false;
bool is_sft_home_active = false;
bool is_sft_end_active = false;

uint16_t ctrl_tab_timer = 0;
uint16_t alt_tab_timer = 0;
uint16_t alt_left_timer = 0;
uint16_t alt_right_timer = 0;
uint16_t sft_down_timer = 0;
uint16_t sft_left_timer = 0;
uint16_t sft_right_timer = 0;
uint16_t sft_up_timer = 0;
uint16_t sft_home_timer = 0;
uint16_t sft_end_timer = 0;

#define _QWERTY  0
#define _LOWER   1
#define _RAISE   2
#define _NAVI    3
#define _YELLOW  4

enum custom_keycodes {
  CTRL_TAB = SAFE_RANGE,
  ALT_TAB,
  DT_ESC_MUTE,
  DT_DEL_POWER,
  DT_HOM_PGUP,
  DT_END_PGDW,
  ALT_LEFT,
  ALT_RIGHT,
  SFT_DOWN,
  SFT_LEFT,
  SFT_RIGHT,
  SFT_UP,
  SFT_HOME,
  SFT_END,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Audio mute
    [DT_ESC_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_AUDIO_MUTE),
    [DT_DEL_POWER] = ACTION_TAP_DANCE_DOUBLE(KC_DELETE, KC_SYSTEM_POWER),
    [DT_HOM_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_PGUP),
    [DT_END_PGDW] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_PGDN),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT( \
  TD(DT_ESC_MUTE),  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  KC_TAB,           KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPACE, \
  CTRL_TAB,         KC_A,   KC_S, LT(3, KC_D),KC_F,    KC_G,                     KC_H,    KC_J, LT(4, KC_K),KC_L,    KC_SCLN, KC_QUOT, \
  ALT_TAB,          KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(DT_DEL_POWER), \
       OSM(MOD_LCTL),MT(MOD_LSFT, KC_LGUI),TT(_LOWER), KC_SPC,           KC_ENT,  TT(_RAISE), 111100000, OSM(MOD_LALT) \
),


[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______,  _______, _______, _______, _______,     _______,\
  _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_0,     KC_7,    KC_8,    KC_9,    KC_ASTERISK, KC_BSPACE, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_PLUS,  KC_4,    KC_5,    KC_6,    KC_EQUAL,    KC_DOT, \
  KC_F1,   _______, _______, _______, _______, _______, _______, _______, KC_MINUS, KC_1,    KC_2,    KC_3,    KC_SLASH,    KC_COMMA, \
                       OSM(MOD_LCTL), _______, _______, KC_SPC,  KC_ENT,  _______,  _______, OSM(MOD_LALT)\
),


[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_MPRV, KC_PSCR, KC_MNXT, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, TD(DT_HOM_PGUP), KC_VOLD, KC_MPLY, KC_VOLU, TD(DT_END_PGDW),     _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______,   _______, _______, _______, _______ \
),


[_NAVI] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, SFT_HOME,SFT_UP,  SFT_END, _______, _______, \
  _______, _______, ALT_LEFT,_______,ALT_RIGHT,_______,                   _______, SFT_LEFT,SFT_DOWN,SFT_RIGHT,_______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, _______, _______, _______, _______, _______ \
),
  
[_YELLOW] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_BRIU, KC_UP,   KC_BRID, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, _______, _______, _______, _______, _______ \
  ) 
};

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  
  switch (keycode) {               
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
      case CTRL_TAB:
      if (record->event.pressed) {
        if (!is_ctrl_tab_active) {
          is_ctrl_tab_active = true;
          register_code(KC_LCTRL);
        }
        ctrl_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
      case ALT_LEFT:
      if (record->event.pressed) {
        if (!is_alt_left_active) {
          is_alt_left_active = true;
          register_code(KC_LALT);
        }
        alt_left_timer = timer_read();
        register_code(KC_LEFT);
      } else {
        unregister_code(KC_LEFT);
      }
      break;
      case ALT_RIGHT:
      if (record->event.pressed) {
        if (!is_alt_right_active) {
          is_alt_right_active = true;
          register_code(KC_LALT);
        }
        alt_right_timer = timer_read();
        register_code(KC_RGHT);
      } else {
        unregister_code(KC_RGHT);
      }
      break;
      case SFT_DOWN:
      if (record->event.pressed) {
        if (!is_sft_down_active) {
          is_sft_down_active = true;
          register_code(KC_LSFT);
        }
        sft_down_timer = timer_read();
        register_code(KC_DOWN);
      } else {
        unregister_code(KC_DOWN);
      }
      break;
      case SFT_LEFT:
      if (record->event.pressed) {
        if (!is_sft_left_active) {
          is_sft_left_active = true;
          register_code(KC_LSFT);
        }
        sft_left_timer = timer_read();
        register_code(KC_LEFT);
      } else {
        unregister_code(KC_LEFT);
      }
      break;
      case SFT_RIGHT:
      if (record->event.pressed) {
        if (!is_sft_right_active) {
          is_sft_right_active = true;
          register_code(KC_LSFT);
        }
        sft_right_timer = timer_read();
        register_code(KC_RGHT);
      } else {
        unregister_code(KC_RGHT);
      }
      break;
      case SFT_UP:
      if (record->event.pressed) {
        if (!is_sft_up_active) {
          is_sft_up_active = true;
          register_code(KC_LSFT);
        }
        sft_up_timer = timer_read();
        register_code(KC_UP);
      } else {
        unregister_code(KC_UP);
      }
      break;
      case SFT_HOME:
      if (record->event.pressed) {
        if (!is_sft_home_active) {
          is_sft_home_active = true;
          register_code(KC_LSFT);
        }
        sft_home_timer = timer_read();
        register_code(KC_HOME);
      } else {
        unregister_code(KC_HOME);
      }
      break;
      case SFT_END:
      if (record->event.pressed) {
        if (!is_sft_end_active) {
          is_sft_end_active = true;
          register_code(KC_LSFT);
        }
        sft_end_timer = timer_read();
        register_code(KC_END);
      } else {
        unregister_code(KC_END);
      }
      break;
  }
  return true;
}
void matrix_scan_user(void) {     # The very important timer.
  if (is_ctrl_tab_active) {
    if (timer_elapsed(ctrl_tab_timer) > 1000) {
      unregister_code(KC_LCTRL);
      is_ctrl_tab_active = false;
    }
  }
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_alt_left_active) {
    if (timer_elapsed(alt_left_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_left_active = false;
    }
  }
  if (is_alt_right_active) {
    if (timer_elapsed(alt_right_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_right_active = false;
    }
  }
  if (is_sft_down_active) {
    if (timer_elapsed(sft_down_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_down_active = false;
    }
  }
  if (is_sft_left_active) {
    if (timer_elapsed(sft_left_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_left_active = false;
    }
  }
  if (is_sft_right_active) {
    if (timer_elapsed(sft_right_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_right_active = false;
    }
  }
  if (is_sft_up_active) {
    if (timer_elapsed(sft_up_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_up_active = false;
    }
  }
  if (is_sft_home_active) {
    if (timer_elapsed(sft_home_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_home_active = false;
    }
  }
  if (is_sft_end_active) {
    if (timer_elapsed(sft_end_timer) > 10) {
      unregister_code(KC_LSFT);
      is_sft_end_active = false;
    }
  }                           
}
