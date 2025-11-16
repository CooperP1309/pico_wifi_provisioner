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
 
    // keep ensure no exit so that background threads stay active
    while(1) {

        int num = 0;
        uint8_t macs[6 * 8];  // room for up to 8 stations

        cyw43_wifi_ap_get_stas(&cyw43_state, &num, macs);

        printf("AP: %d station(s) connected\n", num);
        for (int i = 0; i < num; ++i) {
            uint8_t *m = &macs[i * 6];
            printf("  STA %d: %02X:%02X:%02X:%02X:%02X:%02X\n",
                i,
                m[0], m[1], m[2], m[3], m[4], m[5]);
        }

        sleep_ms(5000);
    }

    return 0;
}