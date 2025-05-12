//
// Created by Human Race on 11/05/2025.
//

#include "weight_serial_com.h"
#include "driver/serial_com_interface.h"
#include "config/include_header.h"
#include "driver/hx711_interface.h"
#include "logic/weight.h"
#include "logic/tare.h"
#include "logic/calibration.h"

void serial_command_handler(const char* line);

void serial_com_init() {
  serial_computer_init();
  serial_computer_set_command_callback(serial_command_handler);
}

void serial_com_loop() {
  float berat = weight_get_gram();
  float kg = weight_get_kg();
  float ton = weight_get_ton();
  uint32_t offset = hx711_get_offset();

  // baca input dari komputer setiap loop
  serial_computer_process_input();      // dari serial_com_interface

  serial_print_str("Berat : ");
  serial_print_float(berat, 2);
  serial_println_str(" gram");
  serial_print_str("Berat : ");
  serial_print_float(kg, 2);
  serial_println_str(" kg");
  serial_print_str("Berat : ");
  serial_print_float(ton, 2);
  serial_println_str(" ton");
  serial_print_str("offset : ");
  serial_print_int(offset);
  serial_println_str(" ");
}

void serial_command_handler(const char* line) {
  // ============================
  // Perintah: TARE
  // ============================
  if (strcmp(line, "t") == 0) {
    if (tare_execute()) {
      serial_println_str("✅ TARE berhasil");
    } else {
      serial_println_str("❌ TARE gagal");
    }
    return;
  }

  // ============================
  // Perintah: CALIB [angka]
  // Contoh: "CALIB 1000"
  // ============================
  if (strncmp(line, "CALIB ", 6) == 0) {
    float berat = atof(&line[6]);
    if (berat > 0.0f) {
      if (calibration_execute(berat)) {
        serial_print_str("✅ Kalibrasi dengan berat");
        serial_print_float(berat, 2);
        serial_println_str(" gram");
      } else {
        serial_println_str("❌ Kalibrasi gagal");
      }
    } else {
      serial_println_str("⚠️ Format salah. Gunakan: CALIB 1000");
    }
    return;
  }

  // ============================
  // Jika tidak cocok
  // ============================
  serial_println_str("❌ Perintah tidak dikenal");
}