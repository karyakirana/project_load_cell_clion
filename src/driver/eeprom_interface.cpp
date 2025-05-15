//
// Created by Human Race on 11/05/2025.
//

#include "eeprom_interface.h"
#include "config/config_pin.h" // alamat EEPROM ada di sini
#include <EEPROM.h>

extern "C" {

// OFFSET
bool eeprom_set_offset(uint32_t offset) {
  EEPROM.put(ADDR_OFFSET, offset);
  return true;
}
bool eeprom_get_offset(uint32_t* out) {
  if (!out) return false;
  EEPROM.get(ADDR_OFFSET, *out);
  if (isnan(*out) || isinf(*out)) {
    *out = 0.0f;
    return false;
  }
  return true;
}

// SCALE
bool eeprom_set_scale(float scale) {
  EEPROM.put(ADDR_SCALE, scale);
  return true;
}
bool eeprom_get_scale(float* out) {
  if (!out) return false;
  EEPROM.get(ADDR_SCALE, *out);
  if (isnan(*out) || isinf(*out)) {
    *out = 0.0f;
    return false;
  }
  return true;
}

// LAST UNITS
bool eeprom_set_last_units(float value) {
  EEPROM.put(ADDR_LAST_UNITS, value);
  return true;
}
bool eeprom_get_last_units(float* out) {
  if (!out) return false;
  EEPROM.get(ADDR_LAST_UNITS, *out);
  if (isnan(*out) || isinf(*out)) {
    *out = 0.0f;
    return false;
  }
  return true;
}

}