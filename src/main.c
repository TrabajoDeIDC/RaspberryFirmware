#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 0

int main() {
  stdio_init_all();

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed");
    return -1;
  }

  while (true) {
    printf("Hello, Pico!\n");
    cyw43_arch_gpio_put(LED_PIN, GPIO_ON);
    sleep_ms(500);
    cyw43_arch_gpio_put(LED_PIN, GPIO_OFF);
    sleep_ms(500);
  }
  return 0;
}
