//
// Created by Human Race on 12/05/2025.
//

#include "ui_lcd_calibration.h"

#include "driver/hx711_interface.h"
#include "driver/eeprom_interface.h"
#include "logic/tare.h"
#include "ui_lcd_button.h"
#include "driver/lcd_interface.h"

#define INPUT_LEN 12

enum gramature {GRAM, KG, TON, UNKNOWN};

static const char* finish_menu[] = { "RETRY", "FINISH" };
static uint8_t finish_menu_selected = 0;

static calibration_state_t state = STATE_CALIBRATION_START;

static global_mode_t global_mode_val = NORMAL_MODE; // default GLOBAL STATE

static enum gramature gramature_val = GRAM;

static const char* err = NULL;
static float latest_known_weight_gram = 0.0f;
static float latest_scale_factor = 1.0f;
static uint32_t offset_val = 0;
static float input_val = 0.0f;
static char input_lcd_val[13] = {0};
static uint8_t cursor_pos = 0;

static void calibration_start(void);
static void calibration_input_init(void);
static void calibration_input(void);
static void calibration_save(void);
static void calibration_finish(void);

static void btn_next(void);
static void btn_previous(void);
static void btn_up(void);
static void btn_change_gramature_input(void);
static void change_num_at_cursor(int8_t delta);

static void latest_known_weigt_float_to_char();

static void finish_menu_render(void);
static void finish_menu_switcher(void);
static void finish_menu_btn_select(void);

static void get_latest_known_weight_gram(void);

void ui_lcd_calibration_init() {
  //
}

void ui_lcd_calibration_update(global_mode_t* global_state) {
  serial_print_str("STATE : ");
  serial_print_int(state);
  serial_print_str("\n");
  switch (state) {
    case STATE_CALIBRATION_START:
      calibration_start();
      break;
    case STATE_CALIBRATION_START_NEW_SCALE:
      calibration_start();
      break;
    case STATE_CALIBRATION_INPUT_INIT:
      calibration_input_init();
      break;
    case STATE_CALIBRATION_INPUT:
      calibration_input();
      break;
    case STATE_CALIBRATION_SAVE:
      calibration_save();
      break;
    case STATE_CALIBRATION_FINISH:
      calibration_finish();
      break;

    default: STATE_IDLE:
      break;
  }
}

static void calibration_start(void) {
  serial_println_str("calibration start");
  // initialize
  err = NULL;
  latest_known_weight_gram = 0.0f;
  latest_scale_factor = 1.0f;
  offset_val = 0;
  input_val = 0.0f;
  memset(input_lcd_val, 0, sizeof(input_lcd_val));

  if (state == STATE_CALIBRATION_START) {
    // get latest known weight from eeprom
    serial_println_str("calibration start line 102");
    if (!eeprom_get_last_units(&latest_scale_factor)) {
      serial_println_str("calibration start line 104");
      state = STATE_CALIBRATION_FINISH;
      err = "EEPROM CALIBRATION ERROR";
      serial_println_str("EEPROM LATEST UNIT ERROR");
      return;
    }
    // get latest scale factor
    if (!eeprom_get_scale(&latest_scale_factor)) {
      serial_println_str("calibration start line 112");
      state = STATE_CALIBRATION_FINISH;
      err = "EEPROM SCALE ERROR";
      serial_println_str("EEPROM SCALE ERROR");
      return;
    }
  }

  serial_println_str("calibration start line 120");

  // tare process
  if (!tare_execute()) {
    serial_println_str("calibration start line 122");
    state = STATE_CALIBRATION_FINISH;
    err = "TARE ERROR";
    serial_println_str("TARE ERROR");
    return;
  }

  serial_println_str("calibration start line 131");
  offset_val = hx711_get_offset();
  // ubah state ke proses selanjutnya
  state = STATE_CALIBRATION_INPUT_INIT;
  serial_println_str("calibration start line 138");
}

static void calibration_input_init(void) {
  serial_println_str("calibration input init");
  // initialize
  // reset lcd
  lcd_cursor_on();
  lcd_set_cursor(0, 0);
  lcd_print_string("                ");
  lcd_set_cursor(0, 1);
  lcd_print_string("                ");
  // set calibration val display
  if (latest_known_weight_gram == 0.0f) {
    input_val = 1000.0f;
  } else {
    input_val = latest_known_weight_gram;
  }
  // float to string
  latest_known_weigt_float_to_char();
  cursor_pos = 0;
  state = STATE_CALIBRATION_INPUT;
}

static void latest_known_weigt_float_to_char() {
  char buffer[13];
  dtostrf(input_val, 6, 2, buffer);
  int8_t len = strlen(buffer);
  int8_t padding = 12 - len;

  memset(input_lcd_val, ' ', 12);
  memcpy(input_lcd_val + padding, buffer, len);
  input_lcd_val[12] = '\0'; // null terminated
}

static void calibration_input(void) {
  serial_println_str("calibration input");
  lcd_set_cursor(0, 0);
  lcd_print_string(input_lcd_val);
  if (gramature_val == KG) {
    lcd_print_string("KG");
    lcd_set_cursor(0, 1);
    lcd_print_string("MODE : KG");
  } else if (gramature_val == TON) {
    lcd_print_string("TON");
    lcd_set_cursor(0, 1);
    lcd_print_string("MODE : TON");
  } else {
    lcd_print_string("GR");
    lcd_set_cursor(0, 1);
    lcd_print_string("MODE : GRAM");
  }
  lcd_set_cursor(cursor_pos, 0);
  // serial_println_str("calibration start line 170");
  // btn prev
  btn_previous();
  // serial_println_str("calibration start line 173");
  // btn next
  btn_next();
  // serial_println_str("calibration start line 176");
  // btn change char number
  btn_up();
  // serial_println_str("calibration start line 176");
  // btn change gramature val
  btn_change_gramature_input();
  // serial_println_str("calibration start line 182");
}

static void calibration_save(void) {
  serial_println_str("calibration save");
}

static void calibration_finish(void) {
  serial_println_str("calibration finish");
  //
  finish_menu_render();
  // selected button
  if (button_is_pressed(BTN_A) || button_is_pressed(BTN_B)) {
    finish_menu_switcher();
  }
  // ok button
}

static void btn_next(void) {
  if (button_is_pressed(BTN_B)) {
    serial_println_str("button next");
    do {
      cursor_pos = (cursor_pos + 1) % INPUT_LEN;
    } while (input_lcd_val[cursor_pos] == '.');

    lcd_set_cursor(cursor_pos, 0);
  }
}

static void btn_previous(void) {
  if (button_is_pressed(BTN_A)) {
    serial_println_str("button prev");
    do {
      if (cursor_pos == 0)
        cursor_pos = INPUT_LEN - 1;
      else
        cursor_pos--;
    } while (input_lcd_val[cursor_pos] == '.');
    lcd_set_cursor(cursor_pos, 0);
  }
}

static void btn_up(void) {
  if (button_is_pressed(BTN_C)) {
    change_num_at_cursor(+1);
  }
}

static void btn_change_gramature_input(void) {
  if (button_is_pressed(BTN_D)) {
    gramature_val++;
    if (gramature_val >= UNKNOWN) {
      gramature_val = GRAM;
    }
  }
}

static void change_num_at_cursor(int8_t delta) {
  char current = input_lcd_val[cursor_pos];

  if (current >= '0' && current <= '9' || current == ' ') {
    int8_t digit = (current == ' ') ? 0 : (current - '0'); // spasi dihitung 0
    digit += delta;

    // wrap-around
    if (digit > 9) digit = 0;
    if (digit < 0) digit = 9;

    input_lcd_val[cursor_pos] = '0' + digit;
    lcd_set_cursor(0, 0);
    lcd_print_string(input_lcd_val);
    lcd_set_cursor(cursor_pos, 0);
  }
}

static void finish_menu_render(void) {
  lcd_clear();
  lcd_set_cursor(0, 0);

  lcd_print_string("[");
  lcd_print_string(finish_menu[0]);
  lcd_print_string("]");

  lcd_print_string("[");
  lcd_print_string(finish_menu[1]);
  lcd_print_string("]");

  // Tampilkan cursor berkedip di posisi yang dipilih
  uint8_t cursor_col = (finish_menu_selected == 0) ? 1 : 10;
  lcd_set_cursor(cursor_col, 0);
  lcd_cursor_on();
  lcd_blink_on();
}

static void finish_menu_switcher(void) {
  finish_menu_selected = (finish_menu_selected == 0) ? 1 : 0;
  finish_menu_render();
}
static void finish_menu_btn_select(void);

static bool save_calibration(float known_weight_gram, uint32_t raw_val) {
  uint32_t offset_val = 0;
  uint32_t delta = 0;
  float new_scale_factor_val = 0.0f;
  // latest scale factor value
  float latest_scale_factor_val = hx711_get_scale();
  // get offset
  offset_val = hx711_get_offset();
  // hitung new scale factor
  delta = (raw_val - offset_val);
  new_scale_factor_val = delta / known_weight_gram;
  // save to eeprom
  bool status_save = eeprom_set_scale(new_scale_factor_val);
  if (!status_save) return false;
  bool eeprom_set_latest_gram = eeprom_set_scale(known_weight_gram);
  if (!eeprom_set_latest_gram) {
    // rollback
    eeprom_set_scale(latest_scale_factor_val);
    hx711_set_scale(latest_scale_factor_val);
  }
  return true;
}

/**
 * @brief Mengambil input dari user melalui ui LCD 16x2 dan 3 tombol
 * @return float
 */
static float known_weight_gram_input() {
  // get known weight input from serial
  const char* weight_str_val[12] = {0};
  // change latest_known_weight gram to string if > 0
  if (latest_known_weight_gram < 1.0f) {
    // default value input
  } else {
    // float to string
  }
  return 0.0f;
}

static void get_latest_known_weight_gram(void) {
  float val = 0.0f;
  // get & check latest_known_weight_gram from eeprom
  if (eeprom_get_last_units(& val)) {
    latest_known_weight_gram = val;
    return;
  }
}

