#include "lwip/tcp.h"
#include "pico/cyw43_arch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcp_client.h"

struct tcp_pcb *pcb[4];
ip_addr_t ips[4];
float *msg_data[4];
int ids[4] = {0, 1, 2, 3};
bool connected_flag[4] = {false, false, false, false};

#define http_request                                                           \
  "POST /data?lat=%f&lng=%f8&temp=%f&humidity=%f&air=%f&noise=%f "             \
  "HTTP/1.1\r\nHost: localhost:8080\r\nConnection: close\r\n\r\n"

int tcp_client_init(float *data, int ip1, int ip2, int ip3, int ip4, int port) {

  int id = 0;
  bool searching = true;

  while (searching) {
    if (connected_flag[id] == false) {
      pcb[id] = tcp_new();
      searching = false;
      printf("Connection %d created haha\n", id);
    } else {
      id++;
    }
    if (id == 4) {
      printf("No more connections available\n");
      return -1;
    }
  }

  msg_data[id] = data;

  if (pcb[id] == NULL) {
    printf("Error creating connection\n");
    return -1;
  }

  IP4_ADDR(&ips[id], ip1, ip2, ip3, ip4);

  tcp_arg(pcb[id], &ids[id]);
  tcp_recv(pcb[id], mssg_recv);

  err_t err = tcp_connect(pcb[id], &ips[id], port, connected);

  if (err != ERR_OK) {
    printf("Error connecting\n");
    return -1;
  }

  return id;
}

err_t connected(void *arg, struct tcp_pcb *tpcb, err_t err) {
  int id = *(int *)arg;

  if (err != ERR_OK) {
    return err;
  }

  printf("Conexion %d stablished\n", id);
  return ERR_OK;
}

void send_data(int id) {
  if (pcb[id] == NULL)
    return;

  char *http_req = (char *)malloc(sizeof(http_request) * 2);
  sprintf(http_req, http_request, msg_data[id][0], msg_data[id][1],
          msg_data[id][2], msg_data[id][3], msg_data[id][4], msg_data[id][5]);

  struct pbuf *p;
  p = pbuf_alloc(PBUF_TRANSPORT, strlen(http_req), PBUF_RAM);
  memcpy(p->payload, http_req, strlen(http_req));

  tcp_write(pcb[id], p->payload, p->len, TCP_WRITE_FLAG_COPY);

  free(http_req);
  pbuf_free(p);
}

err_t mssg_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
  int id = *(int *)arg;

  printf("Message received from %d:\n%s", id, (char *)p->payload);

  tcp_close(tpcb);
  connected_flag[id] = false;
  return ERR_OK;
}

/* err_t connected(void *arg, struct tcp_pcb *tpcb, err_t err) { */
/*   printf("Connected\n"); */

/*   struct pbuf *p; */
/*   p = pbuf_alloc(PBUF_TRANSPORT, strlen(http_request), PBUF_RAM); */
/*   memcpy(p->payload, http_request, strlen(http_request)); */

/*   tcp_write(pcb, p->payload, p->len, TCP_WRITE_FLAG_COPY); */

/*   pbuf_free(p); */

/*   return ERR_OK; */
/* } */
