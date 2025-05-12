//
// Created by Human Race on 11/05/2025.
//

#include "filter.h"

//
// ==========================================================
// MOVING AVERAGE FILTER (MA) - Integer Version
// ==========================================================
//

void ma_init(MAFilter* f, int32_t* buffer, int size) {
  f->buffer = buffer;
  f->size = size;
  f->index = 0;
  f->count = 0;
  f->sum = 0;
}

int32_t ma_update(MAFilter* f, int32_t value) {
  if (f->count < f->size) {
    f->count++;
  } else {
    // Kurangi nilai lama dari sum sebelum ditimpa
    f->sum -= f->buffer[f->index];
  }

  f->buffer[f->index] = value;
  f->sum += value;

  f->index = (f->index + 1) % f->size;

  return (int32_t)(f->sum / f->count);
}

bool ma_is_full(MAFilter* f) {
  return f->count >= f->size;
}

int32_t ma_get_avg(MAFilter* f) {
  if (f->count == 0) return 0;
  return (int32_t)(f->sum / f->count);
}

void ma_reset(MAFilter* f) {
  f->index = 0;
  f->count = 0;
  f->sum = 0;
}

//
// ==========================================================
// EXPONENTIAL MOVING AVERAGE (EMA) - Integer Version
// ==========================================================
//

void ema_init(EMAFilter* f, uint8_t alpha_percent) {
  if (alpha_percent > 100) alpha_percent = 100;
  f->alpha_percent = alpha_percent;
  f->ema = 0;
  f->initialized = false;
}

int32_t ema_update(EMAFilter* f, int32_t value) {
  if (!f->initialized) {
    f->ema = value;
    f->initialized = true;
  } else {
    // Rumus integer: EMA = α * baru + (1-α) * lama
    f->ema = (f->alpha_percent * value + (100 - f->alpha_percent) * f->ema) / 100;
  }
  return f->ema;
}

int32_t ema_get(EMAFilter* f) {
  return f->ema;
}

void ema_reset(EMAFilter* f) {
  f->ema = 0;
  f->initialized = false;
}