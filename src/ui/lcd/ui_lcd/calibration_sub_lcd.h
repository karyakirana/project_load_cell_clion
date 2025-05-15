//
// Created by Human Race on 15/05/2025.
//

#ifndef CALIBRATION_SUB_LCD_H
#define CALIBRATION_SUB_LCD_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

void calibration_sub_lcd_init(void);

void set_lcd_weight_val(float val);

bool calibration_input_render();

#ifdef __cplusplus
}
#endif


#endif //CALIBRATION_SUB_LCD_H
