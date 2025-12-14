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

    if (1 /*wifi_credentials->ssid[0] == '\0' || gpio_rst_btn_pressed()*/) {
        printf("[main] no credentials extracted, begining provisioning\n");
        pico_prov_begin(&wifi_credentials);
    }

    while(wifi_credentials.ssid[0] == '\0') {
        cyw43_arch_poll();
        sleep_ms(1);
    }

    printf("\nI'm FREEEEEEEEE\n");
 
    return 0;
}