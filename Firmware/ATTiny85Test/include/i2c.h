#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>
#include <gpio.h>

// this implements register i2c according to the following datasheet under paragraph 15. USI on page 108
// https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf

// Registers:
#define USICR (*(volatile uint8_t*)0x0D) // USI Control Register on page 116 under 15.5.4
#define USIDR (*(volatile uint8_t*)0x0F) // USI Data Register p.115, 15.5.1
#define USIBR (*(volatile uint8_t*)0x10) // USI Buffer Register (readonly copy of USI Data Register) p.115, 15.5.2

#define USISR (*(volatile uint8_t*)0x0E) // USI Status Register p.115, 15.5.3

// Constants:
#define TWO_WIRE_MODE 0b10 // Two wire mode setting under USI Control Register on page 116 under 15.5.4
#define SOFTWARE_CLOCK_STROBE 0b001 // set I2C clock source with SET_CLOCK_SOURCE to software clock strobe

#define SCL_PIN_NUM 2
#define SCL_PORT B

#define SDA_PIN_NUM 0
#define SDA_PORT B

// Macros:
#define SET_WIRE_MODE(mode) (USICR = (USICR & 0b11001111) | (((mode) & 0b11) << 4))
#define SET_CLOCK_SOURCE(mode) (USICR = (USICR & 0b11110001) | (((mode) & 0b111) << 1))
#define SHIFT_NEXT() (USICR |= 0b10) // shifts next bit
#define CLEAR_I2C_COUNTER() do { \
        (USISR &= 0b11110000) /*reset the four counter bits in USISR*/ \
        USISR |= 0b01000000; /*reset the counter overflow interrupt flag*/ \
    } while(0)
#define GET_ACK() (!(USIDR & 0b1))

// CONFIG_PIN_OUTPUT is configured as low by default
#define SET_SDA() CONFIG_PIN_OUTPUT(SDA_PORT, SDA_PIN_NUM)
#define RELEASE_SDA() CONFIG_PIN_INPUT(SDA_PORT, SDA_PIN_NUM)
#define READ_SDA() READ_PIN(SDA_PORT, SDA_PIN_NUM)

// CONFIG_PIN_OUTPUT is configured as low by default
#define SET_SCL() CONFIG_PIN_OUTPUT(SCL_PORT, SCL_PIN_NUM)
#define RELEASE_SCL() CONFIG_PIN_INPUT(SCL_PORT, SCL_PIN_NUM)
#define READ_SCL() READ_PIN(SCL_PORT, SCL_PIN_NUM)

// process:
/*
init:
    SET_WIRE_MODE(TWO_WIRE_MODE)
    SET_CLOCK_SOURCE(SOFTWARE_CLOCK_STROBE)

write:
    set USIDR to wanted data
    CLEAR_I2C_COUNTER()

    RELEASE_SDA()
    RELEASE_SCL()
    wait until READ_SCL == 1
    SET_SDA() start condition
    SET_SCL()
    while (!READ_SCL()) clock streching

    SHIFT_NEXT() x16 at a valid frequency
    RELEASE_SDA()
    SHIFT_NEXT() x2 for ACK period (at a valid frequency)
    ack = GET_ACK()

    SET_SDA() stop condition
    RELEASE_SCL()
    wait until READ_SCL == 1
    RELEASE_SDA()

    return ack

read:
    CLEAR_I2C_COUNTER()
    RELEASE_SDA()
    RELEASE_SCL()
    wait until READ_SCL == 1
    SET_SDA() start condition
    SET_SCL()
    while (!READ_SCL()) clock streching

    SHIFT_NEXT() x16 at a valid frequency

    val = USIDR

    USIDR = 0x00
    SET_SDA()
    CLEAR_I2C_COUNTER()
    SHIFT_NEXT() x2

    return val
*/

void i2c_init();

#endif // _I2C_H_