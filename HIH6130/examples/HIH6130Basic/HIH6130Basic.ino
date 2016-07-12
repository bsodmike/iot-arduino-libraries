/*
 * HIH6130Basic.ino
 * Example sketch for using the HIH6130 Library for reading relative humidity and temperature data from the Honeywell HIH6130 sensor.
 *
 * Created by Michael de Silva (http://desilva.io) for Inertialbox.
 *
 * Version 0.1.0: 12/07/2016 - initial version
 *
 * MIT license, all text above must be included in any redistribution
 * If you find it useful, buy me a corona beer someday.
 */

#include <Arduino.h>
#include <Wire.h>     //I2C library
#include "HIH6130.h"

#define PULSE_LED     4
#define PULSE_DELAY   100

// Default pinout on the SFE Thing
#define I2C_SDA       2
#define I2C_SCL       14
#define SENSOR_PWR    12

const byte I2C_ADDRESS = 0x27;

HIH6130 sensor(I2C_ADDRESS, SENSOR_PWR);

void setup() {
  setupPulseLED();
  setupI2C();

  Serial.begin(115200);
  Serial.println("Booting");

  String pulse_message = "pulsing GPIO";
  Serial.println(pulse_message + PULSE_LED + " with a " + PULSE_DELAY + "ms delay.");
  Serial.println();

  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>");
  sensor.powerSensor();
}

void loop(void) {
  byte status;
  unsigned int hum_data, temp_data;
  float humidity, temperature;

  status = sensor.read(&hum_data, &temp_data);
  humidity = (float)hum_data;
  temperature = (float)temp_data;

  // do what you like with the sensor data here.

  pulse();            // 200ms delay
}

void setupPulseLED(void) {
  pinMode(PULSE_LED, OUTPUT);
}

void pulse()
{
  digitalWrite(PULSE_LED, HIGH);
  delay(PULSE_DELAY);
  digitalWrite(PULSE_LED, LOW);
  delay(PULSE_DELAY);
}

/*
 * I2C
 */

void setupI2C(void) {
  Wire.begin(I2C_SDA, I2C_SCL);
}

