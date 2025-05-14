//
// Created by Human Race on 12/05/2025.
//

#ifndef UI_LCD_BUTTON_H
#define UI_LCD_BUTTON_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  BTN_NONE = 0,
  BTN_A,
  BTN_B,
  BTN_C,
  BTN_D,
} button_code_t;

// API untuk cek status tombol
void button_init(void);
bool button_is_pressed(button_code_t button);
bool button_is_combo(button_code_t button_1, button_code_t button_2);
bool button_is_long_pressed(button_code_t button, uint8_t duration_ms);
bool button_is_combo_long_pressed(button_code_t button_1, button_code_t button_2, uint32_t duration_ms);
bool button_is_combo_close(button_code_t button_1, button_code_t button_2);

#ifdef __cplusplus
}
#endif

#endif //UI_LCD_BUTTON_H
