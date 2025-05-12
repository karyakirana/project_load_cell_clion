//
// Created by Human Race on 11/05/2025.
//

#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Inisialisasi EEPROM jika perlu (opsional tergantung implementasi).
 */
void eeprom_interface_init(void);

// ----- OFFSET -----
bool eeprom_set_offset(uint32_t offset);
bool eeprom_get_offset(uint32_t* out);

// ----- SCALE FACTOR -----
bool eeprom_set_scale(float scale);
bool eeprom_get_scale(float* out);

// ----- LAST UNITS (terakhir terbaca) -----
bool eeprom_set_last_units(float value);
bool eeprom_get_last_units(float* out);

#ifdef __cplusplus
}
#endif

#endif //EEPROM_INTERFACE_H
