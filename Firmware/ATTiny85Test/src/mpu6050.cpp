#include <mpu6050.h>

uint8_t mpu6050_readReg(uint8_t reg, uint8_t& failed) {
    Wire.beginTransmission(MPU6050_ADDRESS);
    if (Wire.write(reg) == 0) {
        failed = FAILED;
        return 0x00;
    }
    if (Wire.endTransmission(true) != 0) {
        failed = FAILED;
        return 0x00;
    }
    if (Wire.requestFrom(MPU6050_ADDRESS, 1, true) != 1) {
        failed = FAILED;
        return 0x00;
    }
    failed = SUCCESS;
    return Wire.read();
}

uint8_t mpu6050_getData(uint8_t startReg, uint8_t* data, uint8_t amount) {
    Wire.beginTransmission(MPU6050_ADDRESS);
    if (Wire.write(startReg) == 0) 
        return FAILED;
    if (Wire.endTransmission(true) != 0)
        return FAILED;
    if (Wire.requestFrom(MPU6050_ADDRESS, amount, true) != amount)
        return FAILED;
    for (uint8_t i = 0; i < amount; i++)
        data[i] = Wire.read();
    return SUCCESS;
}

uint8_t mpu6050_writeReg(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(MPU6050_ADDRESS);
    if (Wire.write(reg) == 0)
        return FAILED;
    if (Wire.write(data) == 0)
        return FAILED;
    if (Wire.endTransmission(true) != 0)
        return FAILED;
    return SUCCESS;
}

bool mpu6050_isAvailable(uint8_t& failed) {
    return mpu6050_readReg(MPU6050_WHO_AM_I, failed) == MPU6050_DEVICE_ID;
}