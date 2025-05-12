//
// Created by Human Race on 11/05/2025.
//

#ifndef TARE_H
#define TARE_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Lakukan proses TARE:
  * - Baca nilai raw dari HX711
  * - Simpan ke EEPROM
  * - Apply via hx711_set_offset()
  * - Reset tampilan berat
  *
  * @return true jika sukses, false jika gagal
*/
bool tare_execute(void);

/**
  * Coba muat offset dari EEPROM dan apply ke HX711.
  *
  * @return true jika berhasil, false jika EEPROM kosong / tidak valid
  */
bool tare_load_from_eeprom(void);

#ifdef __cplusplus
}
#endif

#endif //TARE_H
