//
// Created by Human Race on 11/05/2025.
//

#include "tare.h"
#include "driver/hx711_interface.h"
#include "driver/eeprom_interface.h"
#include "logic/weight.h"  // untuk reset filter setelah tare

#define RATAAN_PEMBACAAN_TARE 10

bool tare_execute(void) {
  // if (!hx711_is_ready()) {
  //   serial_print_str("hx711 initialization line14 failed\n");
  //   return false;
  // }
  int32_t current_offset = 0;
  int32_t last_offset = hx711_get_offset();

  // proses tar
  hx711_tare(RATAAN_PEMBACAAN_TARE);

  current_offset = hx711_get_offset();

  if (!eeprom_set_offset(current_offset)) {
    // rollback
    hx711_set_offset(last_offset);
    serial_print_str("tare.c line 26");
    return false;  // gagal simpan ke EEPROM
  }

  weight_reset_filter();        // kosongkan berat tampilan
  return true;
}

bool tare_load_from_eeprom(void) {
  uint32_t offset = 0;
  if (!eeprom_get_offset(&offset)) {
    serial_println_str("tare_load_from_eeprom: eeprom_get_offset() failed");
    return false;
  }
  serial_print_str("tare value :");
  serial_print_int(offset);
  serial_print_str("\n");
  hx711_set_offset(offset);     // apply offset yang disimpan
  return true;
}