#ifndef PICODHCP_H
#define PICODHCP_H

class PicoDHCP {
    public:
        int startDHCP();
        int stopAP();

    private:
        dhcp_server_t dhcp_server;

};

int PicoDHCP::startDHCP() {

    // configure dhcp server parameters
    ip4_addr_t gateway_addr;
    p4_addr_t sub_mask;
    IP4_ADDR(&gateway_addr,   192,168,4,1);
    IP4_ADDR(&sub_mask, 255,255,255,0);

    // define network interface for dhcp access point
    struct netif *ap_interface = &cyw43_state.netif[CYW43_ITF_AP];
    netif_set_addr(ap_interface, &gw, &mask, &gw);

    // initialize the dhcp server
    dhcp_server_init(&dhcp_server, );

    return 0;
}

#endif // PICODHCP_H