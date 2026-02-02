#include <Arduino.h>
#include <debug.h>
#include <mpu6050.h>
#include <pac9955b.h>
#include <i2c.h>

enum State {
    MPU_NOT_INITALIZED,
    MPU_INIT,
    MPU_RUNNING
};

int main() {
    init();

    BEGIN_DEBUG;

    uint8_t failed = SUCCESS;
    State state = State::MPU_NOT_INITALIZED;

    uint8_t mpuRawData[MPU6050_ACCELL_DATA];
    float xAccel, yAccel, zAccel;
    float temp;
    float xGyro, yGyro, zGyro;
    bool dataValid = false;

    pac9955b leds;

    while (1) {
        switch (state)
        {
        case State::MPU_NOT_INITALIZED:
            dataValid = false;
            if (mpu6050_isAvailable(failed) && failed == SUCCESS)
                state = State::MPU_INIT;
            break;
        
        case State::MPU_INIT:
            if (MPU_SET_CLOCK_DIVIDER(0) == FAILED) { // fastest clock no division
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            if (MPU_SET_FILTER_BANDWIDTH(0, failed) == FAILED || failed == FAILED) { // disable bandwidth
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            if (MPU_SET_GYRO_RANGE(MPU6050_STANDARD_DEG_P_S_RANGE, failed) == FAILED || failed == FAILED) { // set gyro range to the settings defined value
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            if (MPU_SET_ACCEL_RANGE(MPU6050_STANDARD_G_RANGE, failed) == FAILED || failed == FAILED) { // sets the accel range to the settings defined value
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            if (MPU_SET_PWR_MGMT_1(MPU6050_DEFAULT_POWER_REG) == FAILED) { // sets the power management reg
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            delay(100); // make sure it is running
            state = State::MPU_RUNNING;
            break;
        
        case State::MPU_RUNNING:
            if (mpu6050_getData(MPU6050_ACCELL_OUT, mpuRawData, MPU6050_ACCELL_DATA) == FAILED) {
                state = State::MPU_NOT_INITALIZED;
                break;
            }
            xAccel = (mpuRawData[0] << 8 | mpuRawData[1]) / MPU6050_STANDARD_G_SCALE;
            yAccel = (mpuRawData[2] << 8 | mpuRawData[3]) / MPU6050_STANDARD_G_SCALE;
            zAccel = (mpuRawData[4] << 8 | mpuRawData[5]) / MPU6050_STANDARD_G_SCALE;

            temp = ((mpuRawData[6] << 8 | mpuRawData[7]) / 340.0) + 36.53;

            xGyro = (mpuRawData[8] << 8 | mpuRawData[9]) / MPU6050_STANDARD_DEG_P_S_SCALE;
            yGyro = (mpuRawData[10] << 8 | mpuRawData[11]) / MPU6050_STANDARD_DEG_P_S_SCALE;
            zGyro = (mpuRawData[12] << 8 | mpuRawData[13]) / MPU6050_STANDARD_DEG_P_S_SCALE;

            dataValid = true;
            DB_PRINT(String(xAccel).c_str());
            DB_PRINT(", ");
            DB_PRINT(String(yAccel).c_str());
            DB_PRINT(", ");
            DB_PRINT(String(zAccel).c_str());
            DB_PRINT("   ");
            DB_PRINT(String(temp).c_str());
            DB_PRINT("   ");
            DB_PRINT(String(xGyro).c_str());
            DB_PRINT(", ");
            DB_PRINT(String(yGyro).c_str());
            DB_PRINT(", ");
            DB_PRINTLN(String(zGyro).c_str());
            break;
        }
    }
}