#include "hardware/adc.h"
#include "lwip/tcp.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include <stdio.h>
#include <string.h>

#include "DHT22_Reader.h"
#include "air_quality.h"
#include "noise.h"
#include "tcp_client.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 0

#define DHT22_DATA_PIN 18

#define KY038_ADC_PIN 26
#define KY038_GPIO_PIN 22

float data = 0.0;

float *temperature;
float *humidity;

void set_hostname(const char *hostname) {
  cyw43_arch_lwip_begin();
  struct netif *n = &cyw43_state.netif[CYW43_ITF_STA];
  netif_set_hostname(n, hostname);
  netif_set_up(n);
  cyw43_arch_lwip_end();
}

int init_wifi() {
  if (cyw43_arch_init_with_country(CYW43_COUNTRY_SPAIN)) {
    printf("Wi-Fi init failed\n");
    return -1;
  }

  cyw43_arch_enable_sta_mode();
  set_hostname("pico");

  printf("Connecting to %s\n", WIFI_SSID);
  if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                         CYW43_AUTH_WPA2_AES_PSK, 10000)) {
    printf("failed to connect to %s\n", WIFI_SSID);
    return -1;
  }

  printf("Connected to %s\n", WIFI_SSID);
  return 1;
}

void wait_seconds(int sec) {
  for (int i = sec; i > 0; i--) {
    printf("Starting in %d\n", i);
    sleep_ms(1000);
  }
}

int main() {

  stdio_init_all();
  adc_init();

  if (!init_wifi()) {
    return -1;
  }

  int dht22_id = DHT22_init(DHT22_DATA_PIN, temperature, humidity);

  int tpc1 = tcp_client_init(&data, 192, 168, 1, 155, 4000);
  if (tpc1 < 0) {
    printf("Failed to connect to server\n");
    return 1;
  }

  int tpc2 = tcp_client_init(&data, 192, 168, 1, 1, 80);
  if (tpc2 < 0) {
    printf("Failed to connect to server\n");
    return 1;
  }

  while (1) {
    cyw43_arch_poll();

    DHT22_read(dht22_id);

    printf("Temperature: %f\n", *temperature);
    printf("Humidity: %f\n", *humidity);

    send_data(tpc1);
    send_data(tpc2);
    data++;
    sleep_ms(2000);
  }

  cyw43_arch_deinit();
  return 0;
}
