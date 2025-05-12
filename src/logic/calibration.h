//
// Created by Human Race on 11/05/2025.
//

#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Jalankan proses kalibrasi:
 * - User meletakkan beban diketahui (mass_in_gram)
 * - Dibaca berat dari HX711
 * - Hitung scale factor dan simpan
 *
 * @param mass_in_gram Berat aktual yang diketahui
 * @return true jika sukses, false jika gagal
 */
bool calibration_execute(float mass_in_gram);

/**
 * Coba muat scale factor dari EEPROM dan apply ke HX711.
 *
 * @return true jika berhasil, false jika gagal atau belum pernah disimpan
 */
bool calibration_load_from_eeprom(void);

/**
 * Ambil scale factor yang sedang aktif.
 */
float calibration_get_scale(void);

#ifdef __cplusplus
}
#endif

#endif //CALIBRATION_H
