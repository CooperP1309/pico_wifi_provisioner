#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

#include "wifi_provisioner.h"

int main() {

    // initialize all necessary systems + wifi credentials
    pico_prov_init();

    // begin provisioning if credentials weren't attained after init
    if (!pico_prov_has_credentials() || pico_prov_button_pressed()) {
        pico_prov_ap_begin();
    }
 
    // print the MAC of the picoW wifi interface
    uint8_t mac[6];
    cyw43_wifi_get_mac(&cyw43_state, CYW43_ITF_AP, mac);
    printf("Pico AP MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // ensure background thread stays active
    while(1) {

        // print access point status
        printf("AP up=%d link=%d\n",
        netif_is_up(&cyw43_state.netif[CYW43_ITF_AP]),
        cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_AP));

        sleep_ms(5000);
    }

    return 0;
}