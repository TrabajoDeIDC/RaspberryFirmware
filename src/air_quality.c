#include "air_quality.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

int MQ135READERS_MAX = 4;
MQ135Reader MQ135Readers[4];
int MQ135ReaderCount = 0;

int MQ135_init(int digPin, int anPin, uint16_t *noiselvl, int *noiseDetected) {
  if (MQ135ReaderCount < MQ135READERS_MAX) {

    MQ135Readers[MQ135ReaderCount].digitalPin = digPin;
    MQ135Readers[MQ135ReaderCount].analogPin = anPin;

    MQ135Readers[MQ135ReaderCount].noiseLevel = noiselvl;
    *(MQ135Readers[MQ135ReaderCount].noiseLevel) = 0;

    MQ135Readers[MQ135ReaderCount].noiseDetected = noiseDetected;
    *(MQ135Readers[MQ135ReaderCount].noiseDetected) = 0;

    gpio_init(digPin);
    gpio_set_dir(digPin, GPIO_IN);

    adc_gpio_init(anPin);

    return MQ135ReaderCount++;
  }
  return -1;
}

int MQ135_read(int id) {

  adc_select_input(MQ135Readers[id].analogPin - 26);
  *(MQ135Readers[id].noiseLevel) = adc_read();
}
