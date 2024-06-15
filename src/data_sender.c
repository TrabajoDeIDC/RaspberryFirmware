#include "lwip/tcp.h"
#include "data_sender.h"

#define LOCAL_PORT (u16_t)2345
#define SERVER_PORT (u16_t)8080
#define SERVER_IP 

int connect_to_server() {
  struct tcp_pcb *pcb;

  pcb = tcp_new();
  if (pcb == NULL) {
    puts("Failed to initialise TCP context");
    return 1;
  }

  if (tcp_bind(pcb, IP_ANY_TYPE, LOCAL_PORT) != ERR_OK) {
    puts("Failed to assign TCP context to an IP and a PORT");
    return 1;
  }
  tcp_close(pcb);
  return 0;

}

