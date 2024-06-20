#pragma once

#include "lwip/tcp.h"

int tcp_client_init(float *data, int ip1, int ip2, int ip3, int ip4, int port);
void sethostname(int id, char *hostname);
void send_data(int id);

err_t connected(void *arg, struct tcp_pcb *tpcb, err_t err);
err_t mssg_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
