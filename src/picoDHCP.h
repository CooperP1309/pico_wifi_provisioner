#ifndef PICODHCP_H
#define PICODHCP_H

class PicoDHCP {
    public:
        int startDHCP();
        int stopAP();

    private:
        dhcp_server_t dhcp_server;
        /*
            Fun fact: "_t" is to destinguish that object as a type
        */

};

int PicoDHCP::startDHCP() {

    // initialize gateway and subnet address
    ip4_addr_t gateway_addr;
    ip4_addr_t sub_mask;
    IP4_ADDR(&gateway_addr,   192,168,4,1);
    IP4_ADDR(&sub_mask, 255,255,255,0);

    // initialize network interface for dhcp access point
    /*
        Note: netif data structure holds data regaurding the network
        interface device. In this case, we provide the data from
        the pico wifi chip (given by yw43_state.netif).
    */
    struct netif *ap_interface = &cyw43_state.netif[CYW43_ITF_AP];
    netif_set_addr(ap_interface, &gateway_addr, &sub_mask, &gateway_addr);
    // in this case, the wifi chip is the interface AND the gateway. Therefore, we
    // pass the gateway address twice

    // initialize the dhcp server
    /*
        details on the dhcp functions:
        https://github.com/raspberrypi/pico-examples/blob/master/pico_w/wifi/access_point/dhcpserver/dhcpserver.h
    
        pass a pointer to each structure for mutation of the original data struct instances.
    */
    dhcp_server_init(&dhcp_server, &gateway_addr, &sub_mask);

    return 0;
}

#endif // PICODHCP_H