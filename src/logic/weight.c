//
// Created by Human Race on 11/05/2025.
//

#include "weight.h"
#include "driver/hx711_interface.h"

// =============================
// API Implementation
// =============================

#define GRAM_THRESHOLD 0.5f

static byte times_read = 1;

static float gram = 0.0f;
static float latest_gram = 0.0f;

void weight_init(void) {
  hx711_init();
}

void weight_update(void) {
  if (!hx711_is_ready()) return;

  gram = hx711_get_units(times_read);  // hasil sudah dalam gram (offset+scale)
  if (fabsf(gram) >= GRAM_THRESHOLD) {
    latest_gram = gram;
  }
}

int32_t weight_get_raw(void) {
  return hx711_read_raw();
}

float weight_get_gram() {
  return latest_gram;
}

float weight_get_kg(void) {
  return latest_gram / 1000.0f;
}

float weight_get_ton(void) {
  return latest_gram / 1000000.0f;
}

void weight_reset_filter(void) {
  gram = 0.0f;
  latest_gram = 0.0f;
}