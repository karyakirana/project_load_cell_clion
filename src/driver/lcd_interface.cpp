//
// Created by Human Race on 12/05/2025.
//

#include "lcd_interface.h"
#include "LiquidCrystal_I2C.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

extern "C" {

  void lcd_interface_init(void) {
    lcd.init();
    lcd.backlight();
    lcd.clear();
  }

  void lcd_clear(void) {
    lcd.clear();
  }

  void lcd_set_cursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
  }

  void lcd_print_str(const char* text) {
    lcd.print(text);
  }

  void lcd_println_str(const char* text) {
    lcd.print(text);
    lcd.setCursor(0, 1);  // pindah ke baris berikutnya
  }

  void lcd_render_line1(const char* text) {
    lcd.setCursor(0, 0);
    lcd.print("                ");  // bersihin baris
    lcd.setCursor(0, 0);
    lcd.print(text);
  }

  void lcd_render_line2(const char* text) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(text);
  }

  // ========================
  // Cursor + Blinking
  // ========================
  void lcd_cursor_on(void) {
    lcd.cursor();
  }

  void lcd_cursor_off(void) {
    lcd.noCursor();
  }

  void lcd_blink_on(void) {
    lcd.blink();
  }

  void lcd_blink_off(void) {
    lcd.blink();
  }

  // =================================
  // Ubah Karakter di posisi tertentu
  // =================================
  void lcd_change_char(uint8_t col, uint8_t row, char* buffer, int8_t delta) {
    // Pindah posisi
    lcd.setCursor(col, row);
    // Tidak ada fungsi langsung untuk baca karakter, jadi perlu tracking sendiri
    // Solusi : panggil print ulang karakter dengan nilai + delta

    // ⚠️ Diasumsikan karakter di layar adalah digit atau huruf ASCII
    // -> Kita harus tracking karakter sebelumnya di kode utama
    // Misalnya kita tahu karakter awal '3'
    // Simulasi: ganti '3' jadi '4'

    // Karena LCD tidak bisa membaca karakter yang ditampilkan,
    // maka kita perlu tracking buffernya di luar (di C)

    // Contoh penggunaan ideal:
    // - kita punya char buffer[16]
    // - kita ubah buffer[col] += delta
    // - lalu kita panggil lcd.setCursor(col, row); lcd.print(buffer[col]);

    // Jadi ini versi placeholder:
    char current = buffer[col];
    if (current >= '0' && current <= '9') {
      int digit = current - '0';
      digit += delta;
      if (digit > 9) digit = 0;
      if (digit < 0) digit = 9;
      buffer[col] = '0' + digit;
    }

    lcd.setCursor(col, row);
    lcd.print(buffer[col]);
  }

  void lcd_render_edit_int(const char* label, int32_t value, uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
    lcd.print(label);
    lcd.print(": ");
    lcd.print(value);
  }

  void lcd_render_edit_float(const char* label, float value, uint8_t precision, uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
    lcd.print(label);
    lcd.print(": ");
    lcd.print(value, precision);
  }

}