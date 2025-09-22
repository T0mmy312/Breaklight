# LED Research

Instead of using a dot matrix, a decision has been made to use SMD-LEDs.

- Due to the StVo, a minimum of **1 cd per LED** is required.

## Options

### Found on Conrad
- **Orange LED**  
  - Color: Orange  
  - Forward Voltage (Uf): 2.1 V  
  - Forward Current (If): 20 mA  
  - Brightness: 1000 mcd (≈ 1 cd)  
  - [Link](https://www.conrad.at/de/p/kingbright-kptd-3216seck-smd-led-1206-orange-1000-mcd-35-20-ma-2-1-v-1050405.html)

- **SUPER-RED: OSRAM LS E65F-BBDA-1-1**  
  - Package: SMD-LED PLCC4  
  - Brightness: 2240 mcd (≈ 2.24 cd)  
  - Viewing Angle: 60°  
  - Operating Current: 50 mA  
  - Forward Voltage: 2.15 V  
  - Current Price: **0.32 € / piece**  
  - [Link](https://www.conrad.at/de/p/osram-ls-e65f-bbda-1-1-smd-led-plcc4-super-rot-2240-mcd-60-50-ma-2-15-v-523306.html?utm_source=chatgpt.com)

### Found on Reichelt
- **SMD 3535 Red**
  - Brightness: 19 100 mcd (≈ 19 cd)  
  - Operating Voltage: 2.95 V  
  - Operating Current (max): 350 mA  
  - Current Price: **1.11 € / piece**  
  - [Link](https://www.reichelt.at/at/de/shop/produkt/led_smd_3535_rot_19100_mcd_120_-156298?PROVID=2807&utm_source=chatgpt.com)

# LED driver Ic

We need 12 LEDs to make the 12 bars of light so we need a driver Ic to drive and dim all of the Leds.

## Prerequisits

It has to support 12 LEDs all with PWM output and be able to supply enouth mA to drive the LED (>~50mA).

[Possible LED Driver](https://www.mouser.de/ProductDetail/onsemi/NCV7684DQR2G?qs=sGAEpiMZZMviZ1ygyFMr3k0mYgJpFETSUvBmbUobfcF%252BSml7XHBTxg%3D%3D)