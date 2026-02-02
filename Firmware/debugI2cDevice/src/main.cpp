#include <Arduino.h>
#include <Wire.h>

#define I2C_ADDRESS 0x10  // Change as needed (0x03–0x77)

// Called when data is received from I2C master
void receiveEvent(int numBytes);

void setup() {
    // Initialize serial for USB connection
    Serial.begin(9600);

    // Initialize I2C as a slave
    Wire.begin(I2C_ADDRESS);

    // Register callback for when data is received
    Wire.onReceive(receiveEvent);

    Serial.println("I2C-to-UART bridge ready");
}

void loop() {
    
}

void receiveEvent(int numBytes) {
    while (Wire.available()) {
        char c = Wire.read();
        Serial.write(c);
    }
}