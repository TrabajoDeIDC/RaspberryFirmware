#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/binary_info.h"
#include "hardware/gpio.h"

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

  if (cyw43_arch_init_with_country(CYW43_COUNTRY_SPAIN)) {
    puts("Failed to initialise wifi architecture");
    return 1;
  }
  puts("Wifi architecture initialised succesfully");

  // Enable wifi in station mode
  cyw43_arch_enable_sta_mode();

  // SSID and PASSWORD must be set when building, using '-DWIFI_SSID' and '-DWIFI_PASS'
  if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
    printf("Failed to connect to wifi %s\n", WIFI_SSID);
    return 1;
  }
  printf("Connected succesfully to %s\n", WIFI_SSID);

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

    printf("Temperature: %f\n, Humidity: %f\n", temperature, humidity);
    printf("Noise Level: %d\n", noise_level);
    printf("\n");
  }
  return 0;
}
