#ifndef BLINK_H
#define BLINK_H

#include "pico/stdlib.h"
#include "pico/assert.h"
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 600
#endif

class Blink {
public:
    Blink() {
        int rc = pico_led_init();
        hard_assert(rc == PICO_OK);
    }

    void blink_once() {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }

        void blink_once_quick() {
        pico_set_led(true);
        sleep_ms(200);
        pico_set_led(false);
        sleep_ms(200);
    }

private:
    int pico_led_init() {
    #if defined(PICO_DEFAULT_LED_PIN)
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
        return PICO_OK;
    #elif defined(CYW43_WL_GPIO_LED_PIN)
        return 0;                  //cyw43_arch_init(); We don't want to re-initialize here
    #else
        return PICO_ERROR_GENERIC; // no LED defined
    #endif
    }

    void pico_set_led(bool on) {
    #if defined(PICO_DEFAULT_LED_PIN)
        gpio_put(PICO_DEFAULT_LED_PIN, on);
    #elif defined(CYW43_WL_GPIO_LED_PIN)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    #endif
    }
};

#endif // BLINK_H
