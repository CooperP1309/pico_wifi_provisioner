#include "pico/stdlib.h"
#include "lwip/raw.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/ip.h"
#include "lwip/pbuf.h"
#include "udp_sniffer.h"

static struct raw_pcb *sniffer_pcb = NULL;

// Called for every UDP packet lwIP sees
static u8_t udp_sniffer_recv(void *arg, struct raw_pcb *pcb,
                             struct pbuf *p, const ip_addr_t *addr) {
    (void)arg;
    (void)pcb;
    if (!p) return 0;

    struct ip_hdr *iph = (struct ip_hdr *)p->payload;
    u8_t ihl = IPH_HL(iph) * 4; // IP header length in bytes

    if (p->len < ihl + sizeof(struct udp_hdr)) {
        printf("[SNIFFER] short packet len=%d\n", p->tot_len);
        return 0;
    }

    struct udp_hdr *uh = (struct udp_hdr *)((u8_t *)p->payload + ihl);
    u16_t src_port = lwip_ntohs(uh->src);
    u16_t dst_port = lwip_ntohs(uh->dest);

    const ip_addr_t *dest = ip_current_dest_addr();

    printf("[SNIFFER] UDP dst=%s src_port=%u dst_port=%u len=%d\n",
           ipaddr_ntoa(dest),
           src_port,
           dst_port,
           p->tot_len);

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
