#pragma once
#include "pico/stdlib.h"

typedef struct KY038Reader {
  int digitalPin;
  int analogPin;
  uint16_t *noiseLevel;
  int *noiseDetected;
} KY038Reader;

int KY038_init();
int KY038_read();
