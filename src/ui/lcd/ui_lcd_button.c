//
// Created by Human Race on 12/05/2025.
//

#include "ui_lcd_button.h"
#include "config/config_pin.h"

#define BUTTON_DEBOUNCE_MS 30

static const int8_t button_pins[] = {
  -1, // BTN_NONE
  PIN_A,
  PIN_B,
  PIN_C,
  PIN_D,
};

static uint32_t button_press_start[5] = {0};
static bool button_last_state[5] = {false};
static uint32_t button_combo_time[5] = {0};
static uint32_t button_debounce_time[5] = {0};
static uint32_t last_debounce_time[5] = {0};
static int32_t button_stable_state[5] = {HIGH};
static int32_t button_last_reading[5] = {HIGH};

void button_init(void) {
  for (int i = 1; i <= BTN_D; i++) {
    if (button_pins[i] != -1) {
      pinMode(button_pins[i], INPUT_PULLUP);
    }
    button_press_start[i] = 0;
    button_last_state[i] = false;
    button_combo_time[i] = 0;
    button_debounce_time[i] = 0;
  }
}

bool button_is_pressed(button_code_t button) {
  // if (button <= BTN_NONE || button > BTN_D) return false;
  // return digitalRead(button_pins[button]) == LOW;
  // Asumsikan button adalah 1-4 (BTN_A sampai BTN_D)
  // atau pastikan button_code_t enum nilainya sesuai untuk index array
  if (button <= BTN_NONE || button > BTN_D) return false;

  int current_reading = digitalRead(button_pins[button]);

  // jika bacaan berubah, reset debounce timer
  if (current_reading != button_last_reading[button]) {
    last_debounce_time[button] = millis();
  }

  if ((millis() - last_debounce_time[button]) > BUTTON_DEBOUNCE_MS) {
    // jika sudah cukup waktu, dan bacaan berbeda dari state stabil sebelumnya
    if (current_reading != button_stable_state[button]) {
      button_stable_state[button] = current_reading;
      // jika state stabilnya adalah LOW (ditekan), kembalikan true
      if (button_stable_state[button] == LOW) {
        button_last_reading[button] = current_reading; // simpan bacaan terakhir
        return true; // tombol benar-benar ditekan
      }
    }
  }
  button_last_reading[button] = current_reading; // simpan bacaan terakhir
  return false; // Tombol tidak ditekan atau masih bouncing
}

bool button_is_combo(button_code_t button_1, button_code_t button_2) {
  return button_is_pressed(button_1) && button_is_pressed(button_2);
}

bool button_is_long_pressed(button_code_t button, uint8_t duration_ms) {
  if (button <= BTN_NONE || button > BTN_C) return false;
  bool current_state = digitalRead(button_pins[button]) == LOW;

  if (current_state && !button_last_state[button]) {
    button_press_start[button] = millis();
  }

  button_last_state[button] = current_state;

  return current_state && (millis() - button_press_start[button]) >= duration_ms;
}

bool button_is_combo_long_pressed(button_code_t button_1, button_code_t button_2, uint32_t duration_ms) {
  return button_is_long_pressed(button_1, duration_ms) && button_is_long_pressed(button_2, duration_ms);
}

bool button_is_combo_close(button_code_t button_1, button_code_t button_2) {
  if (button_1 <=BTN_NONE || button_2 <= BTN_NONE || button_1 > BTN_C || button_2 > BTN_C) return false;

  bool pressed_button_1 = digitalRead(button_pins[button_1]);
  bool pressed_button_2 = digitalRead(button_pins[button_2]);

  uint32_t now = millis();

  // update timestamp jika ditekan pertama kali
  if (pressed_button_1 && !button_last_state[button_1]) button_last_state[button_1] = now;
  if (pressed_button_2 && !button_last_state[button_2]) button_last_state[button_2] = now;

  button_last_state[button_1] = pressed_button_1;
  button_last_state[button_2] = pressed_button_2;

  // cek apakah keduanya ditekan dalam jarak waktu pendek
  return pressed_button_1 && pressed_button_2 &&
    abs((int32_t)(button_press_start[button_1] - button_press_start[button_2])) <= 100;
}