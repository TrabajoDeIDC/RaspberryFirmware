/**
 * @file DHT22_Reader.h
 * @brief DHT22 Sensor Reader
 *
 * @author Amancio Gomez Vernet
 * @license GNU General Public License v3.0
 *
 * @details
 * This software is free to use, modify, and distribute under the terms of the
 * GNU General Public License v3.0. See
 * https://www.gnu.org/licenses/gpl-3.0.html for details.
 *
 * This code was heavily inspired by the implementation found at:
 * https://github.com/gosouth/DHT22/blob/master/main/DHT22.c
 */

#include "DHT22_Reader.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/time.h"

// up to 4 sensors connected at once
int DHT22ReaderCount = 0;
DHT22Reader DHT22Readers[DHT22READERS_MAX];

int DHT22_init(int pin, float *temperature, float *humidity) {
  if (DHT22Readers[DHT22ReaderCount].pin == 0) {
    DHT22Readers[DHT22ReaderCount].pin = pin;

    DHT22Readers[DHT22ReaderCount].temperature = temperature;
    *(DHT22Readers[DHT22ReaderCount].temperature) = 0;

    DHT22Readers[DHT22ReaderCount].humidity = humidity;
    *(DHT22Readers[DHT22ReaderCount].humidity) = 0;

    gpio_init(pin);
    return DHT22ReaderCount++;
  }
  return -1;
}

int _getSignalLevel(int id, int state, int timeout) {

  uint64_t starting_time = time_us_64();

  while (gpio_get(DHT22Readers[id].pin) == state) {
    if ((int)(time_us_64() - starting_time) > timeout)
      return -1;
  }

  return (int)(time_us_64() - starting_time);
}

int DHT22_read(int id) {
  uint8_t data_buffer[MSG_BYTE_SIZE];

  gpio_set_dir(DHT22Readers[0].pin, GPIO_OUT);

  gpio_put(DHT22Readers[0].pin, 0);
  sleep_us(3000);

  gpio_put(DHT22Readers[0].pin, 1);
  sleep_us(30);

  gpio_set_dir(DHT22Readers[0].pin, GPIO_IN);

  if (_getSignalLevel(id, 0, 85) < 0)
    return -1;

  if (_getSignalLevel(id, 1, 85) < 0)
    return -1;

  int usec;
  for (int i = 0; i < MSG_BYTE_SIZE * 8; i++) {

    if (_getSignalLevel(id, 0, 56) < 0)
      return -1;

    usec = _getSignalLevel(id, 1, 75);

    if (usec < 0)
      return -1;
    else if (usec > 40)
      data_buffer[i / 8] |= (1 << (7 - (i % 8)));
  }

  *(DHT22Readers[id].humidity) =
      (float)((data_buffer[0] << 8) + data_buffer[1]) / 10;
  *(DHT22Readers[id].temperature) =
      (float)(((data_buffer[2] & 0x7F) << 8) + data_buffer[3]) / 10;

  return 1;
}
