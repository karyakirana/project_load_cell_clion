//
// Created by Human Race on 11/05/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

void logger_log_str(const char* msg);
void logger_log_int(const char* label, int value);
void logger_log_float(const char* label, float value);

#ifdef __cplusplus
}
#endif

#endif //LOGGER_H
