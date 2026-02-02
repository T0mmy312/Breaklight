#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Arduino.h>
#include <Wire.h>

#define DEBUG_MODE true

#define DEBUG_I2C_ADDR 0x10

#if DEBUG_MODE

void dbSendStr(const __FlashStringHelper* fstr);
void dbSendStr(const char* str);

#define BEGIN_DEBUG Wire.begin()
#define DB_PRINT(message) dbSendStr(message)
#define DB_PRINTLN(message) if (1) { \
        DB_PRINT(message); \
        DB_PRINT("\n"); \
    }
#define ERROR(message) if (1) { \
        DB_PRINT(F("Error: ")); \
        DB_PRINTLN(message); \
        while (1) {} \
    }

#else

#define BEGIN_DEBUG ((void)0)
#define DB_PRINT(message) ((void)0);
#define DB_PRINTLN(message) ((void)0);
#define ERROR(message) ((void)0);

#endif

#endif // _DEBUG_H_