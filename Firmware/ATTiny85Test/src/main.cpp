#include <Arduino.h>
#include <debug.h>
#include <Adafruit_MPU6050.h>

int main() {
    init();

    BEGIN_DEBUG;

    Adafruit_MPU6050 mpu;

    if (!mpu.begin()) {
        DB_PRINTLN(F("Sensor init failed"));
        while (1)
            yield();
    }
    DB_PRINTLN(F("Found a MPU-6050 sensor"));

    while (1) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        DB_PRINT(F("Accelerometer "));
        DB_PRINT(F("X: "));
        DB_PRINT(a.acceleration.x);
        DB_PRINT(F(" m/s^2, "));
        DB_PRINT(F("Y: "));
        DB_PRINT(a.acceleration.y);
        DB_PRINT(F(" m/s^2, "));
        DB_PRINT(F("Z: "));
        DB_PRINT(a.acceleration.z);
        DB_PRINTLN(F(" m/s^2"));
    }
}