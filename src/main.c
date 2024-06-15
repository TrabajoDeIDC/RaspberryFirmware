#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "DHT22_Reader.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 0

float temperature;
float humidity;

int main() {
  stdio_init_all();
  adc_init();

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed");
    return -1;
  }

  while (true) {
    cyw43_arch_gpio_put(LED_PIN, GPIO_ON);
    sleep_ms(500);
    cyw43_arch_gpio_put(LED_PIN, GPIO_OFF);
    sleep_ms(500);

    int id = DHT22_init(18, &temperature, &humidity);

    DHT22_read(id);
    printf("Temperature: %f, Humidity: %f\n", temperature, humidity);
  }
  return 0;
}
