//
// Created by Human Race on 11/05/2025.
//
#include "calibration.h"
#include "driver/hx711_interface.h"
#include "driver/eeprom_interface.h"
#include "weight.h"
#include "config/include_header.h"

#define CALIBRATION_SAMPLES    10
#define MIN_MASS_THRESHOLD     0.5f   // Minimal bobot untuk kalibrasi agar valid

static float eeprom_known_weight_val = 0.0f;
static float eeprom_scale_val = 0.0f;

static float scale_factor = 1.0f;  // nilai default defensif

bool calibration_init() {
  // ambil eeprom known weight
  // serial_println_str("calibration_init()");
  if (!eeprom_get_last_units(&eeprom_known_weight_val)) {
    serial_println_str("eeprom_known_weight_val error");
    eeprom_known_weight_val = 0.0f;
    return false;
  }

  if (isnan(eeprom_known_weight_val) || isinf(eeprom_known_weight_val) || eeprom_known_weight_val < 0.0f) {
    serial_println_str("[CAL_LOGIC] last_units dari EEPROM tidak valid/negatif. Reset ke 0.0g.");
    eeprom_known_weight_val = 0.0f;
  }

  // ambil eeprom scale factor
  if (!eeprom_get_scale(&eeprom_scale_val)) {
    serial_println_str("eeprom_scale_val error");
    eeprom_scale_val = 0.0f;
    return false;
  }

  if (isnan(eeprom_scale_val) || isinf(eeprom_scale_val) || eeprom_scale_val < 0.0f) {
    serial_println_str("[CAL_LOGIC] scale dari EEPROM tidak valid/nol. Reset ke 1.0.");
    eeprom_scale_val = 0.0f;
  }

  return true;
}

float calibration_get_known_weight() {
  return eeprom_known_weight_val;
}

bool calibration_execute(float mass_in_gram) {
  if (mass_in_gram < MIN_MASS_THRESHOLD) {
    return false;  // Bobot terlalu kecil → hasil kalibrasi tidak valid
  }

  // if (!hx711_is_ready()) return false;

  // Ambil nilai mentah
  float measured_units = hx711_get_value(CALIBRATION_SAMPLES);  // hasil dari get_value()
  // Ambil nilai scale sebelumnya
  float last_scale = hx711_get_scale();
  if (last_scale == scale_factor) {last_scale = scale_factor;}

  if (fabsf(measured_units) < 0.01f) {
    return false;  // Data terlalu kecil → tidak bisa dibagi
  }

  scale_factor = measured_units / mass_in_gram;

  // Simpan ke EEPROM
  if (!eeprom_set_scale(scale_factor)) {
    hx711_set_scale(last_scale);  // rollback scale
    return false;
  }

  hx711_set_scale(scale_factor);  // Apply langsung
  weight_reset_filter();          // Biar tampilan segar

  return true;
}

bool calibration_load_from_eeprom(void) {
  float stored = 1.0f;

  // serial_println_str("[DEBUG] Masuk ke calibration_load_from_eeprom()");

  if (!eeprom_get_scale(&stored)) {
    serial_println_str("eeprom_get_scale() failed");
    return false;
  }

  if (stored < 0.0001f || isnan(stored) || isinf(stored)) {
    serial_print_str("scale value kacau:");
    serial_print_float(stored, 2);
    serial_print_str("\n");
    return false;
  }

  serial_print_str("scale value :");
  serial_print_int(stored);
  serial_print_str("\n");

  scale_factor = stored;
  hx711_set_scale(scale_factor);
  return true;
}

float calibration_get_scale(void) {
  return scale_factor;
}