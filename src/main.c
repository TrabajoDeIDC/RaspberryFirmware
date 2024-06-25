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

#define MQ135_ADC_PIN 28
#define MQ135_DIG_PIN 15

float data[] = {39.45, -0.38, 0, 0, 0, 0};

float temperature;
float humidity;

uint16_t noiselvl;
int noiseDetected;

uint16_t gasLevel;
int gasDetected;

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

  int dht22_id = DHT22_init(DHT22_DATA_PIN, &temperature, &humidity);

  int ky038_id =
      KY038_init(KY038_GPIO_PIN, KY038_ADC_PIN, &noiselvl, &noiseDetected);

  int mq135_id =
      MQ135_init(MQ135_DIG_PIN, MQ135_ADC_PIN, &gasLevel, &gasDetected);

  while (1) {
    cyw43_arch_poll();

    int tpc1 = tcp_client_init(data, 192, 168, 1, 155, 8080);
    if (tpc1 < 0) {
      printf("Failed to connect to server\n");
      return 1;
    }

    DHT22_read(dht22_id);
    KY038_read(ky038_id);
    MQ135_read(mq135_id);

    data[2] = temperature;
    data[3] = humidity;
    data[4] = (float)gasLevel;
    data[5] = (float)noiselvl;

    printf("Temperature: %f\n", temperature);
    printf("Humidity: %f\n", humidity);

    printf("Noise Level: %d\n", noiselvl);

    printf("Gas Level: %d\n", gasLevel);

    send_data(tpc1);

    sleep_ms(2000);
  }

  cyw43_arch_deinit();
  return 0;
}
