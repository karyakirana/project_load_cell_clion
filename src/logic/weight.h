//
// Created by Human Race on 11/05/2025.
//

#ifndef WEIGHT_H
#define WEIGHT_H

#include "config/include_header.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================================================
// Modul WEIGHT
// ----------------------------------------------------------
// Mengelola pembacaan berat dari HX711
// Output dalam satuan gram, kg, atau ton
// Data diproses melalui EMA (respon cepat) dan MA (rata-rata)
// ==========================================================

/**
 * Inisialisasi HX711 dan filter internal.
 * Harus dipanggil sekali di awal.
 */
void weight_init(void);

/**
 * Harus dipanggil di loop
 */
void weight_update(void);

/**
 * rata-rata dari times pembacaan
 * misalkan ambil rata-rata dari 3 pembacaan
 * default value = 1
 * @param times
 */
void weight_set_times_read(byte times);

/**
 * Ambil raw data pembacaan sensor diluar offset dan scale
 */
int32_t weight_read_raw();

/**
 * Ambil berat dalam satuan gram.
 */
float weight_get_gram();

/**
 * Ambil berat dalam satuan kilogram.
 */
float weight_get_kg(void);

/**
 * Ambil berat dalam satuan ton.
 */
float weight_get_ton(void);

/**
 * Reset filter
 */
void weight_reset_filter(void);

#ifdef __cplusplus
}
#endif

#endif //WEIGHT_H
