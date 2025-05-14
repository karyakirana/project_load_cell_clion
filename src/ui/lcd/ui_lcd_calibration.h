//
// Created by Human Race on 12/05/2025.
//

#ifndef UI_LCD_CALIBRATION_H
#define UI_LCD_CALIBRATION_H

#include "config/include_header.h"
#include "config/config_pin.h"
#include "config/config_state.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  STATE_IDLE,
  STATE_CALIBRATION_START,
  STATE_CALIBRATION_START_NEW_SCALE,
  STATE_CALIBRATION_INPUT_INIT,
  STATE_CALIBRATION_INPUT,
  STATE_CALIBRATION_SAVE,
  STATE_CALIBRATION_FINISH
} calibration_state_t;

void ui_lcd_calibration_init(void);

void ui_lcd_calibration_update(global_mode_t* global_state);

#ifdef __cplusplus
}
#endif

#endif //UI_LCD_CALIBRATION_H
