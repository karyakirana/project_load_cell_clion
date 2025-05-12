//
// Created by Human Race on 11/05/2025.
//

#include "hx711_interface.h"
#include "config/config_pin.h"
#include "HX711.h"

static HX711 scale;

extern "C" {

void hx711_init() {
  scale.begin(PIN_DOUT, PIN_SCK);
}

bool hx711_is_ready() {
  return scale.is_ready();
}

int32_t hx711_read() {
  return scale.read();
}

void hx711_tare(uint8_t times) {
  scale.tare(times);
}

void hx711_set_offset(int32_t offset) {
  scale.set_offset(offset);
}

int32_t hx711_get_offset() {
  return scale.get_offset();
}

void hx711_set_scale(float scale_factor) {
  scale.set_scale(scale_factor);
}

float hx711_get_scale() {
  return scale.get_scale();
}

float hx711_get_units(uint8_t times) {
  return scale.get_units(times);
}

float hx711_get_value(uint8_t times) {
  return scale.get_value(times);
}

} // extern "C"