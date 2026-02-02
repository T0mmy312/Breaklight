#ifndef _MPU_6050_H_
#define _MPU_6050_H_

#include <Wire.h>
#include <debug.h>

#define PRIM_CAT(a, b) a ## b
#define CAT(a, b) PRIM_CAT(a, b)

#define MPU6050_ADDRESS 0x68

// registers
#define MPU6050_WHO_AM_I 0x75 // device id register
#define MPU6050_SMPLRT_DIV 0x19 // sample rate divider
#define MPU6050_CONFIG 0x1A // conifg register
#define MPU6050_GYRO_CONFIG 0x1B // gyro config register
#define MPU6050_ACCEL_CONFIG 0x1C // accelerometer config register
#define MPU6050_PWR_MGMT_1 0x6B // power managemenet register

#define MPU6050_ACCELL_OUT 0x3B // start of all of the sensor output data as follows:
/* so for x, y, z accelleration data we only need to read out the first 6 bytes
3B ACCEL_XOUT_H R ACCEL_XOUT[15:8]
3C ACCEL_XOUT_L R ACCEL_XOUT[7:0]
3D ACCEL_YOUT_H R ACCEL_YOUT[15:8]
3E ACCEL_YOUT_L R ACCEL_YOUT[7:0]
3F ACCEL_ZOUT_H R ACCEL_ZOUT[15:8]
40 ACCEL_ZOUT_L R ACCEL_ZOUT[7:0]
41 TEMP_OUT_H R TEMP_OUT[15:8]
42 TEMP_OUT_L R TEMP_OUT[7:0]
43 GYRO_XOUT_H R GYRO_XOUT[15:8]
44 GYRO_XOUT_L R GYRO_XOUT[7:0]
45 GYRO_YOUT_H R GYRO_YOUT[15:8]
46 GYRO_YOUT_L R GYRO_YOUT[7:0]
47 GYRO_ZOUT_H R GYRO_ZOUT[15:8]
48 GYRO_ZOUT_L R GYRO_ZOUT[7:0]
*/

// constants
#define SUCCESS 0
#define FAILED 1

#define MPU6050_DEVICE_ID 0x68 // device id in the MPU6050_WHO_AM_I register
#define MPU6050_DEFAULT_POWER_REG 0x01 // set clock config to PLL with Gyro X reference and default power management bits

#define MPU6050_ACCELL_DATA 14 // the amount of bytes needed from MPU6050_ACCELL_OUT to get all x, y, z data


#define MPU6050_RANGE_250_DEG_P_S 0 // sets the gyro range in the MPU6050_GYRO_CONFIG register to +-250 deg/s
#define MPU6050_SCALE_250_DEG_P_S 131.0 // scale needed to divide by when in MPU6050_RANGE_250_DEG_P_S to get corret floating point values

#define MPU6050_RANGE_500_DEG_P_S 1 // sets the gyro range in the MPU6050_GYRO_CONFIG register to +-500 deg/s
#define MPU6050_SCALE_500_DEG_P_S 65.5 // scale needed to divide by when in MPU6050_RANGE_500_DEG_P_S to get corret floating point values

#define MPU6050_RANGE_1000_DEG_P_S 2 // sets the gyro range in the MPU6050_GYRO_CONFIG register to +-1000 deg/s
#define MPU6050_SCALE_1000_DEG_P_S 32.8 // scale needed to divide by when in MPU6050_RANGE_1000_DEG_P_S to get corret floating point values

#define MPU6050_RANGE_2000_DEG_P_S 3 // sets the gyro range in the MPU6050_GYRO_CONFIG register to +-2000 deg/s
#define MPU6050_SCALE_2000_DEG_P_S 16.4 // scale needed to divide by when in MPU6050_RANGE_2000_DEG_P_S to get corret floating point values


#define MPU6050_RANGE_2_G 0 // sets the gyro range in the MPU6050_ACCEL_CONFIG register to +-2g
#define MPU6050_SCALE_2_G 16384.0 // scale needed to divide by when in MPU6050_RANGE_2_G to get corret floating point values

#define MPU6050_RANGE_4_G 1 // sets the gyro range in the MPU6050_ACCEL_CONFIG register to +-4g
#define MPU6050_SCALE_4_G 8192.0 // scale needed to divide by when in MPU6050_RANGE_4_G to get corret floating point values

#define MPU6050_RANGE_8_G 2 // sets the gyro range in the MPU6050_ACCEL_CONFIG register to +-8g
#define MPU6050_SCALE_8_G 4096.0 // scale needed to divide by when in MPU6050_RANGE_8_G to get corret floating point values

#define MPU6050_RANGE_16_G 3 // sets the gyro range in the MPU6050_ACCEL_CONFIG register to +-16g
#define MPU6050_SCALE_16_G 2048.0 // scale needed to divide by when in MPU6050_RANGE_16_G to get corret floating point values

// MACROS
#define MPU_SET_CLOCK_DIVIDER(divider) mpu6050_writeReg(MPU6050_SMPLRT_DIV, (divider))
#define MPU_SET_FILTER_BANDWIDTH(val, failed) mpu6050_writeReg(MPU6050_CONFIG, (mpu6050_readReg(MPU6050_CONFIG, (failed)) & 0b11111000) | ((val) & 0b111))
#define MPU_SET_GYRO_RANGE(val, failed) mpu6050_writeReg(MPU6050_GYRO_CONFIG, (mpu6050_readReg(MPU6050_GYRO_CONFIG, (failed)) & 0b11100111) | (((val) & 0b11) << 3))
#define MPU_SET_ACCEL_RANGE(val, failed) mpu6050_writeReg(MPU6050_ACCEL_CONFIG, (mpu6050_readReg(MPU6050_ACCEL_CONFIG, (failed)) & 0b11100111) | (((val) & 0b11) << 3))
#define MPU_SET_PWR_MGMT_1(val) mpu6050_writeReg(MPU6050_PWR_MGMT_1, (val))

// SETTINGS
#define CURRENT_G_RANGE 4 // set this to one of 2, 4, 8 or 16 depending on the needed accel range

#define MPU6050_STANDARD_G_RANGE CAT(CAT(MPU6050_RANGE_, CURRENT_G_RANGE), _G)
#define MPU6050_STANDARD_G_SCALE CAT(CAT(MPU6050_SCALE_, CURRENT_G_RANGE), _G)

#define CURRENT_DEG_P_S_RANGE 500 // set this to one of 250, 500, 1000 or 2000 depending on the needed °/s range

#define MPU6050_STANDARD_DEG_P_S_RANGE CAT(CAT(MPU6050_RANGE_, CURRENT_DEG_P_S_RANGE), _DEG_P_S)
#define MPU6050_STANDARD_DEG_P_S_SCALE CAT(CAT(MPU6050_SCALE_, CURRENT_DEG_P_S_RANGE), _DEG_P_S)

uint8_t mpu6050_readReg(uint8_t reg, uint8_t& failed); // failed != 0 when fails
// caution data has to have space for amount elements or it will fail
uint8_t mpu6050_getData(uint8_t startReg, uint8_t* data, uint8_t amount); // returns 1 when fails
uint8_t mpu6050_writeReg(uint8_t reg, uint8_t data); // returns 1 when fails

bool mpu6050_isAvailable(uint8_t& failed); // failed != 0 when fails

#endif