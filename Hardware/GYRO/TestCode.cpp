#include <Wire.h>
#include <math.h>

#define MPU_ADDR 0x68
int ledPin = 9; // PWM Pin für LED (Arduino Nano)

float ax, ay, az;
float ax_g, ay_g, az_g;
float ax_offset = 0, ay_offset = 0, az_offset = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Wire.begin();

  // MPU aufwecken
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); 
  Wire.write(0x00);
  Wire.endTransmission(true);

  calibrateAccel(); // einmalige Nullpunkt-Kalibrierung
}

void loop() {
  readAccel();

  // Beschleunigung in g
  ax_g = (ax - ax_offset) / 16384.0;
  ay_g = (ay - ay_offset) / 16384.0;
  az_g = (az - az_offset) / 16384.0;

  // simple Brems-Erkennung (X-Achse = Fahrtrichtung)
  if (ax_g < -0.2) {
    analogWrite(ledPin, 255); // volle Helligkeit
  } else {
    analogWrite(ledPin, 80);  // normales Leuchten
  }

  delay(20); // ~50 Hz
}

void readAccel() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  ax = (Wire.read() << 8 | Wire.read());
  ay = (Wire.read() << 8 | Wire.read());
  az = (Wire.read() << 8 | Wire.read());
}

void calibrateAccel() {
  long ax_sum=0, ay_sum=0, az_sum=0;
  for (int i=0; i<200; i++) {
    readAccel();
    ax_sum += ax; ay_sum += ay; az_sum += az;
    delay(5);
  }
  ax_offset = ax_sum / 200.0;
  ay_offset = ay_sum / 200.0;
  az_offset = (az_sum / 200.0) - 16384.0; // sollte 1g sein
}
