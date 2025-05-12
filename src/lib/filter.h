//
// Created by Human Race on 11/05/2025.
//

#ifndef FILTER_H
#define FILTER_H

#include "config/include_header.h"

//
// ==========================================================
// FILTER MODULE (Integer version)
// ----------------------------------------------------------
// MA dan EMA berbasis int32_t (bukan float)
// Efisien untuk Arduino, cocok untuk filter sinyal HX711
// ==========================================================
//

//
// ------------------------------
// MOVING AVERAGE FILTER (MA)
// ------------------------------
// MA menyimpan N data terakhir dan hitung rata-rata integer.
//

typedef struct {
    int32_t* buffer;    // Array eksternal
    int size;
    int index;
    int count;
    int64_t sum;        // Gunakan int64_t untuk mencegah overflow
} MAFilter;

/**
 * Inisialisasi MA.
 * @param f         Pointer filter
 * @param buffer    Buffer eksternal
 * @param size      Ukuran buffer
 */
void ma_init(MAFilter* f, int32_t* buffer, int size);

/**
 * Update filter dengan data baru.
 * @return Nilai rata-rata saat ini
 */
int32_t ma_update(MAFilter* f, int32_t value);

/**
 * Cek apakah buffer sudah penuh
 */
bool ma_is_full(MAFilter* f);

/**
 * Ambil rata-rata saat ini tanpa update
 */
int32_t ma_get_avg(MAFilter* f);

/**
 * Reset isi buffer dan akumulator
 */
void ma_reset(MAFilter* f);

//
// ------------------------------
// EXPONENTIAL MOVING AVERAGE (EMA)
// ------------------------------
// EMA integer, tetap responsif dan ringan
//

typedef struct {
    uint8_t alpha_percent;  // Nilai smoothing (0–100), misal 20 = 0.2
    int32_t ema;
    bool initialized;
} EMAFilter;

/**
 * Inisialisasi EMA.
 * @param f
 * @param alpha_percent   Koefisien smoothing (0–100)
 */
void ema_init(EMAFilter* f, uint8_t alpha_percent);

/**
 * Update dengan nilai baru
 * @return Nilai EMA
 */
int32_t ema_update(EMAFilter* f, int32_t value);

/**
 * Ambil nilai EMA terakhir
 */
int32_t ema_get(EMAFilter* f);

/**
 * Reset EMA
 */
void ema_reset(EMAFilter* f);

#endif //FILTER_H
