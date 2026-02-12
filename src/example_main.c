#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library

#include "wifi_provisioner.h"

// define for wikilift's logging lib
#define RP2040
#include "wl_log.h"

int main() {

    pico_prov_err_t err;
    pico_prov_credentials_t wifi_credentials = {0};

    // initialize all necessary sub systems
    if (stdio_init_all() < 0 || cyw43_arch_init() < 0) {
        return -1;
    }
    sleep_ms(2000);
    wl_log_init();

    WL_LOGI("main", "starting pico wifi provisioner example");

    err = pico_prov_init(&wifi_credentials);
    if (err != PICO_PROV_OK) {
        WL_LOGE("main", "pico_prov_init returned error code: %d", err);

        return err;
    }

    // set case for beginning provisioning
    if (wifi_credentials.ssid[0] == '\0'/* || gpio_rst_btn_pressed()*/) {
        WL_LOGI("main", "no credentials extracted, beginning provisioning");
        
        err = pico_prov_begin(&wifi_credentials);
        if (err != PICO_PROV_OK) {
            return err;
        }

        // set case for polling wifi chip (further polls captive portal)
        while(wifi_credentials.ssid_state == 0) {
            cyw43_arch_poll();
            sleep_ms(1);
        }

        // end pico provisioning (stores passed credentials to flash storage)
        err = pico_prov_end(&wifi_credentials);
        if (err != PICO_PROV_OK) {
            WL_LOGE("main", "pico_prov_end returned error code: %d", err);
            return err;
        }
    }

    WL_LOGI("main", "attempting wifi connection with credentials\n    ssid: \"%s\"\n    password: \"%s\"", wifi_credentials.ssid, wifi_credentials.password);

    return 0;
}