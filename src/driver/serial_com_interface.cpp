//
// Created by Human Race on 11/05/2025.
//

#include "serial_com_interface.h"
#include "config/config_pin.h"

// =========================
// Handler & Buffer
// =========================
#define INPUT_BUFFER_SIZE 64
static char input_buffer[INPUT_BUFFER_SIZE];
static uint8_t input_pos = 0;

static void (*command_handler)(const char* line) = nullptr;

extern "C" {

void serial_computer_init() {
  Serial.begin(BAUDRATE);
  while (!Serial); // Tunggu sampai siap
}

// ==================================================
// Proses input dari komputer
// Dipanggil di loop
// ==================================================
void serial_computer_process_input(void) {
  while (Serial.available()) {
  char c = Serial.read();

  if (c == '\r') continue;  // abaikan carriage return

  if (c == '\n') {
    input_buffer[input_pos] = '\0';  // akhiri string
    input_pos = 0;

      if (command_handler) {
        command_handler(input_buffer);  // panggil handler yang didaftarkan dari .c
      }

    } else if (input_pos < INPUT_BUFFER_SIZE - 1) {
      input_buffer[input_pos++] = c;
    }
  }
}

// ==============================================================
// Daftar handler dari C
// Dipanggil di setup dengan parameter fungsi c yang di-handler
// ==============================================================
void serial_computer_set_command_callback(void (*handler)(const char* line)) {
  command_handler = handler;
}

// =========================
// Print utilities
// =========================

void serial_print_str(const char* str) {
  Serial.print(str);
}

void serial_println_str(const char* str) {
  Serial.println(str);
}

void serial_print_int(int32_t value) {
  Serial.print(value);
}

void serial_print_float(float value, uint8_t decimal_places) {
  Serial.print(value, decimal_places);
}

} // exterm "C"