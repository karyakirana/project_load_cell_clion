//
// Created by Human Race on 12/05/2025.
// Menampilkan weight secara default adalah gram
// Bisa mengubahnya menjadi kg, ton, dan kembali ke gram
// Bisa menjalankan fungsi tare
//

#include "ui_lcd_weight.h"
#include "config/config_pin.h"
#include "config/include_header.h"
#include "driver/lcd_interface.h"

static void ui_init(void);
static void button_init(void);
static void logic_init(void);

static void button_a_init(void);
static void button_b_init(void);
static void button_c_init(void);

static void weight_display(void);
static void weight_tare_display(void);

static void button_change_units(void);
static void button_tare(void);

void ui_lcd_weight_init(void) {
  //
}

void ui_lcd_weight_update(void) {
  //
}