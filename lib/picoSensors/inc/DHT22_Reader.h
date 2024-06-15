/*f
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

#pragma once

#define DHT22READERS_MAX 4
#define MSG_BYTE_SIZE 5

typedef struct DHT22Reader {
  int pin;
  float *temperature;
  float *humidity;
} DHT22Reader;

/**
 * @brief Initializes a DHT22 sensor reader with the specified pin and data
 * pointers.
 *
 * This function initializes a DHT22 sensor reader with the specified GPIO pin
 * number and pointers to store the temperature and humidity readings. It
 * assigns these values to the internal data structure `DHT22Readers`. If the
 * initialization is successful, it returns the index of the initialized reader.
 * If no more readers can be initialized, it returns -1.
 *
 * @param[in] pin The GPIO pin number to which the DHT22 sensor is connected.
 * @param[out] temperature Pointer to a float variable to store the temperature
 * reading.
 * @param[out] humidity Pointer to a float variable to store the humidity
 * reading.
 * @return Index of the initialized DHT22 reader in the `DHT22Readers` array, or
 * -1 if no more readers can be initialized.
 */
int DHT22_init(int pin, float *temperature, float *humidity);

/**
 * @brief Measures the duration a GPIO pin stays at a specified state.
 *
 * This function measures the time (in microseconds) for which a specified
 * GPIO pin remains at a given state (high or low). The measurement is
 * performed using a busy-wait loop, and the function will return after
 * the pin changes state or the timeout is reached.
 *
 * @param[in] id of the DHT22 reader to read from.
 * @param[in] state The GPIO state to measure (true for high, false for low).
 * @param[in] timeout The maximum time to wait (in microseconds) for the pin
 * to change state.
 *
 * @return The duration (in microseconds) the pin stayed at the specified state,
 *         or -1 if the timeout was reached.
 */
int _getSignalLevel(int id, int state, int timeout);

/**
 * @brief Reads data from DHT22 sensor and writes into temp and humidity
 * pointers.
 *
 * This function reads data from a DHT22 sensor, consisting of 16 bits humidity,
 * 16 bits temperature, and an 8-bit checksum. It converts the received binary
 * data into decimal values for temperature and humidity, and checks the
 * checksum to ensure data integrity before writing the results to the specified
 * memory locations pointed to by temp and humidity.
 *
 * @param[out] temp Pointer to a float variable where the temperature value (in
 * Celsius) will be stored.
 * @param[out] humidity Pointer to a float variable where the humidity value (in
 * percentage) will be stored.
 * @return Returns 0 on successful read and checksum verification, or -1 if an
 * error occurred (checksum mismatch).
 *
 */

int DHT22_read(int id);
