//
// Created by Human Race on 11/05/2025.
//

#ifndef HX711_INTERFACE_H
#define HX711_INTERFACE_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

void hx711_init();
bool hx711_is_ready(void);
int32_t hx711_read_raw(void);
void hx711_tare(uint8_t times);
void hx711_set_offset(int32_t offset);
int32_t hx711_get_offset(void);
void hx711_set_scale(float scale_factor);
float hx711_get_scale(void);
float hx711_get_units(uint8_t times); // get_value / scale
float hx711_get_value(uint8_t times); // raw - offset sebelum dibagi dengan scale

#ifdef __cplusplus
}
#endif

#endif //HX711_INTERFACE_H
