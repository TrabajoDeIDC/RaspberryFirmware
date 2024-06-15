#pragma once
#include "pico/stdlib.h"

typedef struct KY038Reader {
  int digitalPin;
  int analogPin;
  uint16_t *noiseLevel;
  int *noiseDetected;
} KY038Reader;

int KY038_init(int digPin, int anPin, uint16_t *noiselvl, int *noiseDetected);
int KY038_read(int id);
