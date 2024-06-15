#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/binary_info.h"
#include "hardware/gpio.h"

#include "DHT22_Reader.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 0

float temperature;
float humidity;

int main() {
  stdio_init_all();

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
