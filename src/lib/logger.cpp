//
// Created by Human Race on 11/05/2025.
//
#include "logger.h"
#include "config/include_header.h"


void logger_log_str(const char* msg) {
  Serial.println(msg);
}

void logger_log_int(const char* label, int value) {
  Serial.print(label);
  Serial.print(": ");
  Serial.println(value);
}

void logger_log_float(const char* label, float value) {
  Serial.print(label);
  Serial.print(": ");
  Serial.println(value, 3); // tampilkan 3 digit desimal
}