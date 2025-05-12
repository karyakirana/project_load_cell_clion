//
// Created by Human Race on 11/05/2025.
//
#include "app.h"
#include "config/include_header.h"
#include "logic/weight.h"
#include "logic/calibration.h"
#include "logic/tare.h"
#include "ui/serial_com/weight_serial_com.h"

void app_init() {
    serial_com_init();
    bool calibration_load = calibration_load_from_eeprom();
    bool tare_load = tare_load_from_eeprom();

    if (!calibration_load) {
        serial_println_str("calibration load failed");
    }
    if (!tare_load) {
        serial_println_str("tare load failed");
    }
    weight_init();
    serial_println_str("initialized");
}

void app_update() {
    weight_update();
    serial_com_loop();
    delay(500);
}