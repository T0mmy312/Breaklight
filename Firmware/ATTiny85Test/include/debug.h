#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Wire.h>

#define DEBUG_MODE true

#define DEBUG_I2C_ADDR 0x10

#if DEBUG_MODE

#define BEGIN_DEBUG Wire.begin()
#define DB_PRINT(message) if (1) { \
        Wire.beginTransmission(DEBUG_I2C_ADDR); \
        Wire.write(message); \
        Wire.endTransmission(); \
    }
#define DB_PRINTLN(message) if (1) { \
        DB_PRINT(message); \
        DB_PRINT("\n") \
    }

#else

#define BEGIN_DEBUG ((void)0)
#define DB_PRINT(message) ((void)0);
#define DB_PRINTLN(message) ((void)0);

#endif

#endif // _DEBUG_H_