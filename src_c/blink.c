#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"    // we assume building for the pico w GPIO is defined

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

// Turn the led on or off
void pico_set_led(bool led_on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}