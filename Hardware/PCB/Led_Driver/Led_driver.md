# PCA9955BTWJ LED Driver Circuit

## Task Description
The goal of this task is to design a schematic using the **PCA9955BTWJ** LED driver from NXP to control twelve **LS E65F-BBDA-1-1** LEDs via an **I²C interface** with a microcontroller (MCU).  
The PCA9955BTWJ regulates the LED current, while the MCU controls brightness and on/off state through I²C communication.

---

## Circuit Description
The **PCA9955BTWJ** is a 16-channel constant-current LED driver with an I²C interface.  
In this circuit, **12 channels (LED0–LED11)** are used to drive twelve LEDs.

---

### Pin Connections

| Pin | Name | Connection |
|-----|------|-------------|
| 1 | REXT | 23 Ω resistor to GND  |
| 2–4 | AD0–AD2 | Connected to GND (I²C address = 0x02) |
| 5 | OE | Connected to GND (outputs always enabled) |
| 6–17 | LED0–LED11 | Connected to LED cathodes |
| 18–20, 24 | VSS | Connected to GND |
| 25 | RESET | Pulled up to +3.3 V via 10 kΩ resistor |
| 26 | SCL | I²C clock line to MCU |
| 27 | SDA | I²C data line to MCU |
| 28 | VDD | +3.3 V power supply |
| 29 | EPAD | Connected to GND |

---

### LED Connections
Each LED cathode (K) is connected to one **LEDx** output of the PCA9955.  
The LED anodes (A1, A2, A3) are all tied to **+3.3 V**.  
No current-limiting resistors are required — the PCA9955 controls the current internally.

---

### Power and Decoupling
- Supply voltage: **+3.3 V**  
- I²C lines **SDA** and **SCL** use **10 kΩ pull-up resistors**  
- Decoupling capacitors placed close to the IC:  
  - **100 nF** and **1 µF** between **VDD** and **GND**

---
