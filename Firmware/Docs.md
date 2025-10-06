# Mcu Research

The goals for the mcu is as low power as possible and as low cost as possible.
It also needs min. 12 Digital output for PWM bitbanging
and basic i2c buses for gyro

contestants:
- STM8L value line:
    - STM8L052R8:
        - 1.50€ / mcu
        - 64kb flash
        - 4kb ram
        - 64 pin
        - 200uA/MHz + 330uA
        - low power modes
        - input voltage max. 3.6V
- ATTiny85:
    - 8 pins
    - one i2c bus
    - platformio
    - 512 Bytes ram

ATTiny85 is probebly the best option because the very simple build and only has 8 pins two of which we need for i2c and maybe a gpio, plus the ATTiny can be connected straight to the battery.

[ATTiny Buy](https://www.mouser.at/ProductDetail/Microchip-Technology/ATTINY85-20SFR?qs=E2PpAYvlWVuiXni206aW5g%3D%3D)

The main problem with the ATTiny is that, because we have so few pins, the pins for programming and i2c collide, so any i2c devices can't be connected while where programming the ATTiny, thats why we have to add a solder brige to deconnect the i2c devices when we want to use the programming pins to flash a software.