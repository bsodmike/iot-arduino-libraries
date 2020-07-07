/*
 * HIH6130.cpp
 * Library for reading relative humidity and temperature data from the Honeywell
 * HIH6130 sensor.
 *
 * Created by Michael de Silva (http://desilva.io) for Inertialbox.
 *
 * Version 0.1.0: 11/07/2016 - initial version
 *
 * MIT license, all text above must be included in any redistribution
 * If you find it useful, buy me a (root) beer someday.
 */

#include <Arduino.h>
#include <Wire.h>     //I2C library
#include "HIH6130.h"

HIH6130::HIH6130(int sensor_address, int power_pin) {
  _i2c_address = sensor_address;
  _power_pin = power_pin;
}

HIH6130::~HIH6130() { }

void HIH6130::powerSensor(void) {
  pinMode(_power_pin, OUTPUT);
  digitalWrite(_power_pin, HIGH); // this turns on the HIH6130
  // Serial.println("Honeywell HIH6130 Humidity & Temperature Sensor turned on.");
  // Serial.println();

  delay(5000);                    // delay for sensor to turn on.
}

/*
 * Retrieve temperature and humidity values from HIH6130
 * Takes humidity and temperature references
 * Updates them inside the function
 * Returns the sensor state as a value directly
 */
byte HIH6130::read(unsigned int *humidity, unsigned int *temperature) {

  byte status, hum_h, hum_l, temp_h, temp_l; // uint8_t

  // Start I2C Transmission
  Wire.beginTransmission(_i2c_address);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  // Typical sensor sample time is ~35ms.
  delay(100);

  // Request 4 bytes of data
  Wire.requestFrom((int) _i2c_address, (int) 4);

  while (Wire.available() == 0) {
    Serial.println("Waiting for data from sensor...");
    delay(10);
  };

  // Read 4 bytes of data
  // humidity msb, humidity lsb, temp msb, temp lsb
  if (Wire.available() == 4) {
    hum_h = Wire.read();
    hum_l = Wire.read();
    temp_h = Wire.read();
    temp_l = Wire.read();
  }

  // Stop I2C Transmission
  Wire.endTransmission();

  // Slice of state bytes
  status = (hum_h >> 6) & 0x03;

  // Serial.print("\nData Byte 1 (Humidity MSB): B");
  // Serial.print(hum_h, BIN);

  // Calculate Relative Humidity & Temperature
  *humidity = (float) ((((unsigned int) (hum_h & 0x3f) << 8) | hum_l) * 100.0) / 16383.0;
  *temperature = (float) (((((((unsigned int) temp_h) << 6) + (temp_l >> 2)) / 16383.0) * 165.0) - 40);

  return(status);
}
