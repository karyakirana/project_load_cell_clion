//
// Created by Human Race on 11/05/2025.
//

#ifndef CONFIG_PIN_H
#define CONFIG_PIN_H

#include "include_header.h"

// Konfigurasi pin hx711
#define PIN_DOUT 4
#define PIN_SCK  5

#endif //CONFIG_PIN_H

// eeprom map
#define ADDR_OFFSET              0
#define ADDR_SCALE               (ADDR_OFFSET + sizeof(uint32_t))
#define ADDR_LAST_UNITS          (ADDR_SCALE + sizeof(float))

// SERIAL COM
#define BAUDRATE 9600
