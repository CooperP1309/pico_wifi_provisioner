#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

#include "wifi_provisioner.h"

int main() {

    pico_prov_credentials_t wifi_credentials = {0};

    // initialize all necessary systems + wifi credentials
    if (pico_prov_init(&wifi_credentials) != PICO_PROV_OK) {
        return -1;
    }

    // begin provisioning if credentials weren't attained after init
    if (1 /* || reset_wifi_btn_pressed()*/) {
        pico_prov_begin();
    }

    while(1) {
        printf("listening...\n");
        sleep_ms(5000);
    }
 
    return 0;
}