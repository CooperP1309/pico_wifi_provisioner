// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

// project headers
#include "wifi_provisioner.h"
#include "pico_fs.h"            // abstraction of flash file i/o functions
#include "pico_ap.h"
#include "pico_dhcp.h"
#include "udp_sniffer.h"

// buffer length = 
// max length of SSID (32 chars) + space + max length of password(63) = 96
char credentials_buffer[96] = {0};  

int pico_prov_init() {
    
    // stdio and wifi chip inits
    if (stdio_init_all() < 0) {
        return -1;
    }
    //if (cyw43_arch_init() < 0) {
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_AUSTRALIA) < 0) {
    return -1;
    }

    sleep_ms(2000);

    // indication of initialization via both serial output and led 
    printf("\nIntializing wifi provisioning...\n");
    blink(250);
    blink(250);
    blink(250);

    // mount the file system for credentails extraction
    if (picofs_init() < 0){
        return -1;
    }

    // actual reading of credentials file  
    if (picofs_read_file(CREDENTIALS_PATH, credentials_buffer, 96) < 0) {
        return -1;
    }

    printf("PicoProv: extracted credentials: %s\n", credentials_buffer);
    printf("PicoProv: has_credentials status: %d\n", pico_prov_has_credentials());
    fflush(stdout);

    return 1; 
}

bool pico_prov_has_credentials() {
    return credentials_buffer[0] != '\0';
}

// TO DO: IMPLEMENT THIS AND DELETE ALWAYS TRUE AFTER CAPTIVE TESTING
bool pico_prov_button_pressed() {
    return true;
}

int pico_prov_ap_begin() {

    udp_sniffer_init();

    // starting of access point
    if (start_ap() < 0){
        return -1;
    }

    // begin listening dhcp server
    dhcp_start();

    return 0;
}

void blink(int blink_length) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(blink_length);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(blink_length);
}