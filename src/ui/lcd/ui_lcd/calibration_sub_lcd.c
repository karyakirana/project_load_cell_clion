//
// Created by Human Race on 15/05/2025.
//

#include "calibration_sub_lcd.h"
#include "driver/lcd_interface.h"
#include "ui/lcd/ui_lcd_button.h"

#define INPUT_LEN 12
#define LCD_REFRESH_RATE 250

enum gramature_mode {GRAM, KG, TON};
static enum gramature_mode gram_mode_val = GRAM;

static float weight_val = 0.0f;
static char weight_display_val[13] = {0};

static uint8_t cursor_col_pos = 0;
static uint8_t cursor_row_pos = 0;

// variabel internal untuk interval update lcd
static uint32_t lcd_refresh_last_time = 0;

static void input_lcd_render(void);
static void latest_weight_val_float_to_char_gr(void);

// btn function and helper of it
static void btn_next(void);
static void btn_prev(void);
static void btn_change(void);
static void change_val_at_cursor();

void calibration_sub_lcd_init() {
  lcd_cursor_on();
  lcd_set_cursor(0, 0);
  lcd_print_string("                ");
  lcd_set_cursor(0, 1);
  lcd_print_string("                ");
}

void set_lcd_weight_val(float val) {
  serial_println_str("calibaration_sub_lcd line 42");
  serial_print_float(val, 2);
  serial_println_str("");
  weight_val = val;
  latest_weight_val_float_to_char_gr();
}

static void latest_weight_val_float_to_char_gr() {
  char buffer[13];
  dtostrf(weight_val, 9, 2, buffer);
  int len = strlen(buffer);
  int padding = 12 - len;

  memset(weight_display_val, ' ', padding);
  memcpy(weight_display_val + padding, buffer, len);
  weight_display_val[12] = '\0';
}

bool calibration_input_render() {
  uint32_t current_time = millis();

  // update tampilan lcd secara periodik
  if (current_time - lcd_refresh_last_time >= LCD_REFRESH_RATE) {
    lcd_refresh_last_time = current_time;
    input_lcd_render();
  }
  btn_next();
  btn_prev();
  btn_change();
  return false;
}

static void input_lcd_render() {
  lcd_set_cursor(0, 0);
  lcd_print_string(weight_display_val);
  switch (gram_mode_val) {
    case TON:
      lcd_print_string("TON");
      lcd_set_cursor(0, 1);
      lcd_print_string("MODE : TON");
      break;
    case KG:
      lcd_print_string("KG");
      lcd_set_cursor(0, 1);
      lcd_print_string("MODE : KG");
      break;
    case GRAM:
    default:
      lcd_print_string("GR");
      lcd_set_cursor(0, 1);
      lcd_print_string("MODE : GRAM");
      break;
  }
  lcd_set_cursor(cursor_col_pos, cursor_row_pos);
}

/*********************************************************
 *
 * BUTTON FUNCTION and HELPER OF IT
 *
 *********************************************************
 */

static void btn_next() {
  if (button_is_pressed(BTN_B)) {
    serial_println_str("btn next pressed");
    do {
      cursor_col_pos = (cursor_col_pos + 1) % INPUT_LEN;
    } while (weight_display_val[cursor_col_pos] == '.');
  }
}

static void btn_prev() {
  if (button_is_pressed(BTN_A)) {
    serial_println_str("btn prev pressed");
    do {
      if (cursor_col_pos == 0)
        cursor_col_pos = INPUT_LEN - 1;
      else
        cursor_col_pos--;
    } while (weight_display_val[cursor_col_pos] == '.');
  }
}

static void btn_change(void) {
  if (button_is_pressed(BTN_C)) {
    change_val_at_cursor();
  }
}

static void change_val_at_cursor() {
  char current = weight_display_val[cursor_col_pos];

  if (current >= '0' && current <= '9' || current == ' ') {
    int8_t digit = (current == ' ') ? 0 : (current - '0'); // spasi dihitung 0
    digit++;

    // wrap-around
    if (digit > 9) digit = 0;
    if (digit < 0) digit = 9;

    weight_display_val[cursor_col_pos] = '0' + digit;
  }
}