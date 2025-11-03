#include <Arduino.h>
#include <debug.h>
#include <LEDDriver.h>

int main() {
    init();

    BEGIN_DEBUG;

    PCA9955B ledDriver;
    
    ledDriver.begin(0.0, LEDDriver::ARDUINO_SHIELD);

    while (1) {
        ledDriver.pwm(0, 0.5);
    }
}