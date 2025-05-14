//
// Created by Human Race on 12/05/2025.
//

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void lcd_interface_init();
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);

void lcd_print_string(const char *str);
void lcd_println_string(const char *str);

void lcd_render_line1(const char* txt);
void lcd_render_line2(const char* txt);

void lcd_cursor_on(void);
void lcd_cursor_off(void);
void lcd_blink_on(void);
void lcd_blink_off(void);

/**
 * @brief ambil karakter di posisi (col, row) ditambah/dikurangi delta
 * cetak kembali ke posisi yang sama
 * @param col
 * @param row
 * @param buffer
 * @param delta
 */
void lcd_change_int(uint8_t col, uint8_t row, char* buffer,int8_t delta);

void lcd_render_edit_int(const char* label, int32_t value, uint8_t col, uint8_t row);
void lcd_render_edit_float(const char* label, float value, uint8_t precision,uint8_t col, uint8_t row);


#ifdef __cplusplus
}
#endif

#endif //LCD_INTERFACE_H
