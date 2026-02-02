#ifndef _PAC9955B_H_
#define _PAC9955B_H_

#include <Wire.h>
#include <debug.h>

// the datasheet used is the following: https://www.nxp.com/docs/en/data-sheet/PCA9955B.pdf

// writing process to the pac9955b:
// once the address and r/w bit is acknowledged a byte must be sent that is set to the controll register which is used as followed:
// controll register:
// [b0; b6]: register index to write to
// b7: Auto-Increment Flag (AIF)
//
// AIF along with AI0 and AI1 from the MODE1 register dictate how auto increment is handled as specified on page 14 in section 7.2 under Table 6

// registers (found on page 15 under section 7.3)
#define MODE1 0x00
#define MODE2 0x01

#define LEDOUT0 0x02
#define LEDOUT1 0x03
#define LEDOUT2 0x04
#define LEDOUT3 0x05

#define GRPPWM 0x06
#define GRPFREQ 0x07

#define PWM0 0x08
#define PWM1 0x09
#define PWM2 0x0A
#define PWM3 0x0B
#define PWM4 0x0C
#define PWM5 0x0D
#define PWM6 0x0E
#define PWM7 0x0F
#define PWM8 0x10
#define PWM9 0x11
#define PWM10 0x12
#define PWM11 0x13
#define PWM12 0x14
#define PWM13 0x15
#define PWM14 0x16
#define PWM15 0x17

#define IREF0 0x18
#define IREF1 0x19
#define IREF2 0x1A
#define IREF3 0x1B
#define IREF4 0x1C
#define IREF5 0x1D
#define IREF6 0x1E
#define IREF7 0x1F
#define IREF8 0x20
#define IREF9 0x21
#define IREF10 0x22
#define IREF11 0x23
#define IREF12 0x24
#define IREF13 0x25
#define IREF14 0x26
#define IREF15 0x27

// constants
#define SUCCESS 0
#define FAILED 1

#define ADDR_GND 0
#define ADDR_PD 1
#define ADDR_FLT 2
#define ADDR_PU 3
#define ADDR_VDD 4

#define LED_OFF 0b00 // from page 20 section 7.3.3
#define LED_ON 0b01
#define LED_PWM 0b10
#define LED_PWM_GROUP 0b11

#define LDR0_REG 0 // from page 20 section 7.3.3
#define LDR1_REG 0
#define LDR2_REG 0
#define LDR3_REG 0

#define LDR4_REG 1
#define LDR5_REG 1
#define LDR6_REG 1
#define LDR7_REG 1

#define LDR8_REG 2
#define LDR9_REG 2
#define LDR10_REG 2
#define LDR11_REG 2

#define LDR12_REG 3
#define LDR13_REG 3
#define LDR14_REG 3
#define LDR15_REG 3

#define LDR0_MASK 0 // from page 20 section 7.3.3
#define LDR1_MASK 2
#define LDR2_MASK 4
#define LDR3_MASK 6

#define LDR4_MASK 0
#define LDR5_MASK 2
#define LDR6_MASK 4
#define LDR7_MASK 6

#define LDR8_MASK 0
#define LDR9_MASK 2
#define LDR10_MASK 4
#define LDR11_MASK 6

#define LDR12_MASK 0
#define LDR13_MASK 2
#define LDR14_MASK 4
#define LDR15_MASK 6

// MACROS
#define PRIM_CAT(a, b) a##b
#define CAT(a, b) PRIM_CAT(a, b)

#define GET_PAC_ADDR(ad0, ad1, ad2) (ad0 + ad1 * 5 + ad2 * 25 + 1)
#define LEDOUT(n) CAT(LEDOUT, n)
#define PWM(n) CAT(PWM, n)
#define IREF(n) CAT(IREF, n)
#define LDR_REG_INDEX(n) CAT(CAT(LDR, n), _REG)
#define LDR_REG(n) LEDOUT(LDR_REG_INDEX(n))
#define LDR_MASK(n) CAT(CAT(LDR, n), _MASK)

// enums
enum pac9955b_Status {
    NOT_INITED,
    INITED,
    ERROR_STATE
};

// structs
typedef struct _pac9955b {
    uint8_t ledout[4] = {0x00, }; // all leds by default off
    uint8_t pwm[16] = {0x00, };
    pac9955b_Status status = pac9955b_Status::NOT_INITED;
    uint8_t addr = 0;
} pac9955b;

// functions

uint8_t pac9955b_init(pac9955b& pac);
uint8_t pac9955b_update(pac9955b& pac);
uint8_t pac9955b_setLedState(pac9955b& pac, uint8_t led, uint8_t state); // LED_OFF, LED_ON, LED_PWM or LED_PWM_GROUP

uint8_t pac9955b_write(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t pac9955b_write_seq(uint8_t addr, uint8_t start_reg, uint8_t amount, uint8_t* vals);

uint8_t pac9955b_read(uint8_t addr, uint8_t reg, uint8_t& failed);
uint8_t pac9955b_read_seq(uint8_t addr, uint8_t reg, uint8_t amount, uint8_t* buffer);

#endif // _PAC9955B_H_