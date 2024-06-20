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

#define http_request "GET / HTTP/1.1\r\nValue: %.2f\r\n\r\n"

int cont = 0;

int tcp_client_init(float *data, int ip1, int ip2, int ip3, int ip4, int port) {
  pcb[cont] = tcp_new();
  msg_data[cont] = data;

  if (pcb[cont] == NULL) {
    return -1;
  }

  IP4_ADDR(&ips[cont], ip1, ip2, ip3, ip4);

  tcp_arg(pcb[cont], &ids[cont]);
  tcp_recv(pcb[cont], mssg_recv);

  err_t err = tcp_connect(pcb[cont], &ips[cont], port, connected);

  if (err != ERR_OK)
    return -1;

  return cont++;
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
  sprintf(http_req, http_request, *msg_data[id]);

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
