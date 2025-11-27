// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

// project headers
#include "pico_ap.h"

int start_ap() {

    // set parameters for the access point
    const char *ssid = "anticipate_wifi";
    const char *password = "anticipate123";

    // start the access point with passed params
    cyw43_arch_enable_ap_mode(ssid, password, CYW43_AUTH_WPA2_MIXED_PSK);
    printf("PicoAP: Wifi Access Point started with SSID: %s\n", ssid);

    return 0;
}

int stop_ap() {

    cyw43_arch_disable_ap_mode();
    printf("PicoAP: Wifi Access Point stopped\n");

    return 0;
}