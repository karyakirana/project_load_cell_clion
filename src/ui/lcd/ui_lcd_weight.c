//
// Created by Human Race on 12/05/2025.
// Menampilkan weight secara default adalah gram
// Bisa mengubahnya menjadi kg, ton, dan kembali ke gram
// Bisa menjalankan fungsi tare
//

#include "ui_lcd_weight.h"

#include "ui_lcd_button.h"
#include "config/config_pin.h"
#include "config/include_header.h"
#include "driver/lcd_interface.h"
#include "logic/weight.h"
#include "logic/tare.h"

enum display_weight_t {
  DISPLAY_GRAM,
  DISPLAY_KG,
  DISPLAY_TON
};

static enum display_weight_t display_mode = DISPLAY_KG;

static uint8_t cursor_pos = 0;
static uint8_t buffer_size = 16-1;

static uint8_t display_idle_val = 0;

// static void button_init(void);
// static void logic_init(void);

static void change_display_mode(void);

static void display_idle(void);
static void weight_display(void);
static void weight_display_kg(void);
static void weight_display_ton(void);
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
  //weight_display();
  change_display_mode();
  if (!display_idle_val) {
    display_idle();
  }

  switch (display_mode) {
    case DISPLAY_GRAM:
      weight_display();
      break;
    case DISPLAY_KG:
      weight_display_kg();
      break;
    case DISPLAY_TON:
    default:
      weight_display_ton();
      break;
  }
}

static void change_display_mode(void) {
  if (button_is_pressed(BTN_C)) {
    switch (display_mode) {
      case DISPLAY_GRAM:
        // Jika mode saat ini GRAM, ubah ke KG
        display_mode = DISPLAY_KG;
        break; // Keluar dari switch setelah melakukan perubahan

      case DISPLAY_KG:
        // Jika mode saat ini KG, ubah ke TON
        display_mode = DISPLAY_TON;
        break; // Keluar dari switch

      case DISPLAY_TON:
        // Jika mode saat ini TON, ubah kembali ke GRAM (menyelesaikan satu siklus)
        display_mode = DISPLAY_GRAM;
        break; // Keluar dari switch
    }
  }
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

static void display_idle(void){
  lcd_set_cursor(0, 0);
  lcd_print_string("            ");
  lcd_set_cursor(0, 1);
  lcd_print_string("            ");
}

static void weight_display(void) {
  // default tampilkan gram
  float gram = weight_get_gram();
  char buf[13] = {0}; // 12 char untuk lcd + 1 '\0'

  // konversi float ke string
  dtostrf(gram, 13, 2, buf);
  lcd_set_cursor(0, 0);
  lcd_print_string("BERAT :         ");
  lcd_set_cursor(0, 1);
  lcd_print_string(buf);
  lcd_print_string("gr ");
  display_idle_val = 1;
}

static void weight_display_kg(void) {
  float kg = weight_get_kg();
  char buf[13] = {0};

  // konversi float to string
  dtostrf(kg, 12, 3, buf);
  lcd_set_cursor(0, 0);
  lcd_println_string("BERAT :         ");
  lcd_print_string(buf);
  lcd_print_string(" kg ");
  display_idle_val = 1;
}

static void weight_display_ton(void) {
  float ton = weight_get_ton();
  char buf[13] = {0};

  // konversi float to string
  dtostrf(ton, 12, 3, buf);
  lcd_set_cursor(0, 0);
  lcd_println_string("BERAT :         ");
  lcd_print_string(buf);
  lcd_print_string(" ton");
  display_idle_val = 1;
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
  delay(50);
  display_idle();
}