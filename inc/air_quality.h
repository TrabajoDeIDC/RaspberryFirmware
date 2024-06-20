#pragma once

#include "pico/stdlib.h"

typedef struct MQ135Reader {
  int digitalPin;
  int analogPin;
  uint16_t *noiseLevel;
  int *noiseDetected;
} MQ135Reader;

int MQ135_init(int digPin, int anPin, uint16_t *gasLevel, int *gasDetected);
int MQ135_read(int id);
