#include <debug.h>
#include <Arduino.h>

void dbSendStr(const __FlashStringHelper* fstr) {
    Wire.beginTransmission(DEBUG_I2C_ADDR);
    PGM_P p = reinterpret_cast<PGM_P>(fstr);
    while (uint8_t c = pgm_read_byte(p++)) {
        Wire.write(c);
    }
    Wire.endTransmission(DEBUG_I2C_ADDR);
}

void dbSendStr(const char* str) {
    Wire.beginTransmission(DEBUG_I2C_ADDR);
    for (uint8_t i = 0; str[i] != '\0'; i++) {
        Wire.write(str[i]);
    }
    Wire.endTransmission(DEBUG_I2C_ADDR);
}