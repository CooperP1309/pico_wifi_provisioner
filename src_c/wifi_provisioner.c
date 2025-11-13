// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

// declaration file
#include "wifi_provisioner.h"

int wifi_provisioner_init() {
    
    // io and gpio inits
    stdio_init_all();
    cyw43_arch_init();
    sleep_ms(2000);             // sleep ensures serial usb output is fully init 

    // indication of initialization via both serial output and led 
    printf("\nIntializing wifi provisioning...\n");
    blink(250);
    blink(250);
    blink(250);

    return 1; 
}

void blink(int blink_length) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(blink_length);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(blink_length);
}
