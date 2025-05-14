//
// Created by Human Race on 11/05/2025.
//
#include "app.h"
#include "config/include_header.h"
#include "config/config_state.h"
#include "logic/weight.h"
#include "logic/calibration.h"
#include "logic/tare.h"
#include "ui/serial_com/weight_serial_com.h"
#include "ui/lcd/ui_lcd_weight.h"
#include "ui/lcd/ui_lcd_calibration.h"
#include "ui/lcd/ui_lcd_button.h"

static global_mode_t global_mode_val = NORMAL_MODE;

static void btn_calibration_mode_active(void);

void app_init() {
    serial_com_init();
    button_init();
    bool calibration_load = calibration_load_from_eeprom();
    bool tare_load = tare_load_from_eeprom();

    if (!calibration_load) {
        serial_println_str("calibration load failed");
    }
    if (!tare_load) {
        serial_println_str("tare load failed");
    }
    weight_init();
    ui_lcd_weight_init();
    ui_lcd_calibration_init();
    serial_println_str("initialized");
}

void app_update() {
    serial_println_str("Mode :");
    if (global_mode_val == NORMAL_MODE) {
        serial_println_str("Normal mode");
    } else if (global_mode_val == UI_LCD_CALIBRATION_MODE) {
        serial_println_str("Calibration mode");
    }
    switch (global_mode_val) {
        case UI_LCD_CALIBRATION_MODE:
            ui_lcd_calibration_update(&global_mode_val);
            break;
        default: NORMAL_MODE:
            weight_update();
            ui_lcd_weight_update();
            serial_com_loop();
            btn_calibration_mode_active();
            break;
    }

    serial_println_str("app updated");
    delay(500);
}

static void btn_calibration_mode_active(void) {
    if (button_is_pressed(BTN_B)) {
        global_mode_val = UI_LCD_CALIBRATION_MODE;
        serial_println_str("button pressed");
        delay(2000);
    }
}