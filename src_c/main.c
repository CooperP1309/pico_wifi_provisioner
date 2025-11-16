#include "wifi_provisioner.h"

int main() {

    // initialize all necessary systems + wifi credentials
    pico_prov_init();

    // begin provisioning if credentials weren't attained after init
    if (!pico_prov_has_credentials() || pico_prov_button_pressed()) {
        pico_prov_ap_begin();
    }
 
    return 0;
}