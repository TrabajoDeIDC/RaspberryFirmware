#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "DHT22_Reader.h"
#include "noise.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 0

#define DHT22_DATA_PIN 18

#define KY038_ADC_PIN 26
#define KY038_GPIO_PIN 22

float temperature;
float humidity;

uint16_t noise_level;
int noise_detected;

int main() {
  stdio_init_all();
  adc_init();

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed");
    return -1;
  }

  int dht22_id = DHT22_init(DHT22_DATA_PIN, &temperature, &humidity);
  int ky038_id =
      KY038_init(KY038_GPIO_PIN, KY038_ADC_PIN, &noise_level, &noise_detected);

  while (true) {
    cyw43_arch_gpio_put(LED_PIN, GPIO_ON);
    sleep_ms(500);
    cyw43_arch_gpio_put(LED_PIN, GPIO_OFF);
    sleep_ms(500);

    DHT22_read(dht22_id);
    KY038_read(ky038_id);

    printf("Temperature: %f\nHumidity: %f\n", temperature, humidity);
    printf("Noise Level: %d\n", noise_level);
    printf("\n");
  }
  return 0;
}
