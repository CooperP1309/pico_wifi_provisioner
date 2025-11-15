// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

// project headers
#include "wifi_provisioner.h"
#include "pico_fs.h"            // abstraction of flash file i/o functions

int wifi_provisioner_init() {
    
    // stdio and wifi chip inits
    if (!stdio_init_all()) {
        return -1;
    }
    if (cyw43_arch_init() < 0) {
        return -1;
    }
    sleep_ms(2000);

    // indication of initialization via both serial output and led 
    printf("\nIntializing wifi provisioning...\n");
    blink(250);
    blink(250);
    blink(250);

    // max length of SSID (32 chars) + max length of password(64) = 96
    char buffer[96];
    picofs_read_file(CREDENTIALS_PATH, buffer, sizeof(buffer)); 

    return 1; 
}

void blink(int blink_length) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(blink_length);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(blink_length);
}
