#ifndef _GPIO_H_
#define _GPIO_H_

#define PRIM_CAT(a, b) a##b
#define CAT(a, b) PRIM_CAT(a, b)

// this is in the following datasheet under p.54, 10.2.1
// https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf

// DDxn bits define the pin direction with 1 for output and is found in the DDRx register
// PORTxn bits define if a pullup is used (1=yes) when configured as input, it drives the given pin high/Low when output is configured. It is found in the PORTx register
// PINxn bits can be read to get the logic level of the pins when configured as input and is found in the PINx register
// to get high Z the pin has to be configured as input

// defines
#define HIGH 1
#define LOW 0

// pin registers
#define PORTB (*(volatile uint8_t*)0x18)
#define DDRB (*(volatile uint8_t*)0x17)
#define PINB (*(volatile uint8_t*)0x16)

// macros
#define DDRx(x) CAT(DDR, x)
#define PORTx(x) CAT(PORT, x)
#define PINx(x) CAT(PIN, x)

#define READ_PIN(port, num) ((PINx(port) >> (num)) & 1)
#define WRITE_PIN(port, num, value) (PORTx(port) = (PORTx(port) & ~(1 << (num))) | (value << (num))) // writes the given logic level to the given pin
#define WRITE_PIN_HIGH(port, num) (PORTx(port) |= 1 << (num))
#define WRITE_PIN_LOW(port, num) (PORTx(port) &= ~(1 << (num)))
#define TOGGLE_PIN(port, num) (PINx(port) |= 1 << (num)) // toggles the given pin when configured as output (relies on the AVR PINx toggle-on-write behavior)

#define CONFIG_PIN_INPUT(port, num) do { \
        DDRx(port) &= ~(1 << (num)); \
        PORTx(port) &= ~(1 << (num)); \
    } while (0)
#define CONFIG_PIN_INPUT_PULLUP(port, num) do { \
        DDRx(port) &= ~(1 << (num)); \
        PORTx(port) |= 1 << (num); \
    } while (0)
#define CONFIG_PIN_OUTPUT(port, num) do { \
        PORTx(port) &= ~(1 << (num)); \
        DDRx(port) |= (1 << (num)); \
    } while (0)

#endif