//
// Created by Human Race on 12/05/2025.
// Menampilkan weight secara default adalah gram
// Bisa mengubahnya menjadi kg, ton, dan kembali ke gram
// Bisa menjalankan fungsi tare
//

#include "ui_lcd_weight.h"
#include "config/config_pin.h"
#include "config/include_header.h"
#include "driver/lcd_interface.h"
#include "logic/weight.h"
#include "logic/tare.h"

static uint8_t cursor_pos = 0;
static uint8_t buffer_size = 16-1;

static void button_init(void);
// static void logic_init(void);

static void weight_display(void);
static void weight_tare_display(void);

// static void button_change_right_cursor(void);
// static void button_change_left_cursor(void);
// static void button_change_units(void);
// static void button_tare(void);

// static uint8_t find_dot_index(const char* buffer);

void ui_lcd_weight_init(void) {
  serial_println_str("[DEBUG] ui_lcd_weight_init]");
  lcd_interface_init();
  //button_init();
}

void ui_lcd_weight_update(void) {
  int status_tombol = digitalRead(PIN_A);
  // serial_print_int(status_tombol);
  // serial_println_str(" --> tombol");
  if (digitalRead(PIN_A) == LOW) {
    weight_tare_display();
  }
  weight_display();
}

// static void button_init(void) {
//   pinMode(PIN_A, INPUT_PULLUP);
//   pinMode(PIN_B, INPUT_PULLUP);
//   pinMode(PIN_C, INPUT_PULLUP);
// }

// static uint8_t find_dot_index(const char* buffer) {
//   const char* ptr = strrchr(buffer, '.');
//   if (ptr != NULL) {
//     return (uint8_t)(ptr - buffer);
//   }
//   return 255;
// }

static void weight_display(void) {
  // default tampilkan gram
  float gram = weight_get_gram();
  char buf[13] = {0}; // 12 char untuk lcd + 1 '\0'

  // konversi float ke string
  dtostrf(gram, 13, 2, buf);
  lcd_set_cursor(0, 0);
  lcd_print_string("Berat :");
  lcd_set_cursor(0, 1);
  lcd_print_string(buf);
  lcd_print_string("gr");

}

static void weight_tare_display(void) {
  lcd_set_cursor(0, 0);
  lcd_print_string("Tare . . .");
  bool tare_status = tare_execute();
  if (!tare_status) {
    lcd_set_cursor(0, 0);
    lcd_print_string("Tare Gagal");
  } else {
    lcd_set_cursor(0, 0);
    lcd_print_string("Tare Selesai");
  }
  // delay(50);
}