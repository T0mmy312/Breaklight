// ===== Globale Offsets =====
float gx_off = 0, gy_off = 0, gz_off = 0;
float ax_off = 0, ay_off = 0, az_off = 0;

// ===== Kalibrierfunktion =====
// Leg das Board ruhig hin und ruf diese Funktion auf
void calibrateMPU6050(int samples = 200) {
  long gx_sum=0, gy_sum=0, gz_sum=0;
  long ax_sum=0, ay_sum=0, az_sum=0;

  for (int i = 0; i < samples; i++) {
    uint8_t buf[14];
    i2cReadBytes(REG_ACCEL_XOUT_H, buf, 14);

    int16_t ax = (int16_t)((buf[0] << 8) | buf[1]);
    int16_t ay = (int16_t)((buf[2] << 8) | buf[3]);
    int16_t az = (int16_t)((buf[4] << 8) | buf[5]);
    int16_t gx = (int16_t)((buf[8] << 8) | buf[9]);
    int16_t gy = (int16_t)((buf[10] << 8) | buf[11]);
    int16_t gz = (int16_t)((buf[12] << 8) | buf[13]);

    gx_sum += gx; gy_sum += gy; gz_sum += gz;
    ax_sum += ax; ay_sum += ay; az_sum += az;

    delay(5); // kleine Pause zwischen den Samples
  }

  gx_off = (float)gx_sum / samples;
  gy_off = (float)gy_sum / samples;
  gz_off = (float)gz_sum / samples;

  // Z-Achse korrigieren: sollte im Stillstand ~+1g messen
  ax_off = (float)ax_sum / samples;
  ay_off = (float)ay_sum / samples;
  az_off = ((float)az_sum / samples) - ACCEL_LSB_PER_G;
}
