#include "pico/stdlib.h"
#include "lwip/raw.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include "udp_sniffer.h"

static struct raw_pcb *sniffer_pcb = NULL;

// Called for every UDP packet lwIP sees
static u8_t udp_sniffer_recv(void *arg, struct raw_pcb *pcb,
                             struct pbuf *p, const ip_addr_t *addr) {
    (void)arg;
    (void)pcb;

    if (!p) {
        return 0;
    }

    // Destination IP of this packet
    const ip_addr_t *dest = ip_current_dest_addr();

    printf("[SNIFFER] UDP packet dst=%s len=%d\n",
           ipaddr_ntoa(dest),
           p->tot_len);

    // VERY IMPORTANT: return 0 and DO NOT free p
    // so normal UDP sockets (like your DHCP server) still see it
    return 0;
}

void udp_sniffer_init(void) {
    sniffer_pcb = raw_new(IP_PROTO_UDP);
    if (!sniffer_pcb) {
        printf("[SNIFFER] raw_new(IP_PROTO_UDP) failed\n");
        return;
    }
    raw_bind(sniffer_pcb, IP_ADDR_ANY);
    raw_recv(sniffer_pcb, udp_sniffer_recv, NULL);
    printf("[SNIFFER] UDP sniffer initialised\n");
}
