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