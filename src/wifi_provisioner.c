// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

// project headers
#include "wifi_provisioner.h"
#include "pico_prov_errors.h"
#include "pico_fs.h"            // abstraction of flash file i/o functions
#include "pico_ap.h"
#include "pico_dhcp.h"

// buffer length = 
// max length of SSID (32 chars) + space + max length of password(63) = 96
char credentials_buffer[96] = {0};  

pico_prov_err_t pico_prov_init(pico_prov_credentials_t *wifi_credentials) {
    
    // stdio and wifi chip inits
    if (stdio_init_all() < 0 || cyw43_arch_init() < 0) {
        return PICO_PROV_ERR_INIT;
    }

    sleep_ms(2000);

    // indication of initialization via both serial output and led 
    printf("\nintializing wifi provisioning...\n");
    blink(250);
    blink(250);
    blink(250);

    // mount the file system for credentails extraction
    if (pico_fs_init() == PICO_PROV_ERR_FS_MOUNT){
        return PICO_PROV_ERR;
    }

    // actual reading of credentials file  
    if (pico_fs_read_file(CREDENTIALS_PATH, credentials_buffer, 96) == PICO_PROV_ERR_FS_READ) {
        printf("PicoProv: reading from file failed\n");
        return PICO_PROV_ERR;
    }

    printf("PicoProv: extracted credentials: %s\n", credentials_buffer);

    fflush(stdout);

    return PICO_PROV_OK; 
}

int pico_prov_begin() {
    
    // starting of access point
    if (start_ap() < 0){
        return -1;
    }

    // begin listening dhcp server
    if (pico_dhcp_start() < 0) {
        return -1;
    }

    return 0;
}

void sort_credentials_buffer() {

}

void blink(int blink_length) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(blink_length);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(blink_length);
}