//
// Created by Human Race on 11/05/2025.
//

#ifndef SERIAL_COM_INTERFACE_H
#define SERIAL_COM_INTERFACE_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

void serial_computer_init();

// Harus dipanggil berkala (loop) untuk memproses input dari komputer.
void serial_computer_process_input(void);

/**
 * Daftarkan handler fungsi perintah dari komputer.
 * Handler akan dipanggil setiap satu baris input selesai.
 * Contoh input: "TARE", "CALIB 1000"
 */
void serial_computer_set_command_callback(void (*handler)(const char* line));

void serial_print_str(const char* str);
void serial_println_str(const char* str);

void serial_print_int(int32_t value);
void serial_print_float(float value, uint8_t decimal_places);

#ifdef __cplusplus
}
#endif

#endif //SERIAL_COM_INTERFACE_H
