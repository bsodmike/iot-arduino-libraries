/*
 * Created by Michael de Silva (http://desilva.io) for Inertialbox.
 *
 * MIT license, all text above must be included in any redistribution
 * If you find it useful, buy me a (root) beer someday.
 */

#ifndef LIB_HIH6130_H_
#define LIB_HIH6130_H_

class HIH6130 {

  public:
    HIH6130(int sensor_address, int power_pin);
    ~HIH6130();

    void powerSensor(void);
    byte read(unsigned int *humidity, unsigned int *temperature);

  private:
    int _i2c_address;
    int _power_pin;
};

#endif
