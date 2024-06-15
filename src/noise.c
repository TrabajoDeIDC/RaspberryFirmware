#include "noise.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

int KY038READERS_MAX = 4;
KY038Reader KY038Readers[4];
int KY038ReaderCount = 0;

int KY038_init(int digPin, int anPin, uint16_t *noiselvl, int *noiseDetected) {
  if (KY038ReaderCount < KY038READERS_MAX) {

    KY038Readers[KY038ReaderCount].digitalPin = digPin;
    KY038Readers[KY038ReaderCount].analogPin = anPin;

    KY038Readers[KY038ReaderCount].noiseLevel = noiselvl;
    *(KY038Readers[KY038ReaderCount].noiseLevel) = 0;

    KY038Readers[KY038ReaderCount].noiseDetected = noiseDetected;
    *(KY038Readers[KY038ReaderCount].noiseDetected) = 0;

    gpio_init(digPin);
    gpio_set_dir(digPin, GPIO_IN);

    adc_gpio_init(anPin);

    return KY038ReaderCount++;
  }
  return -1;
}

int KY038_read(int id) {

  adc_select_input(KY038Readers[id].analogPin - 26);
  *(KY038Readers[id].noiseLevel) = adc_read();
}
