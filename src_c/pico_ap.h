#ifndef PICO_AP_H
#define PICO_AP_H

class Pico_AP {
    public:
        int start_ap();
        int stop_ap();
};

int Pico_AP::start_ap() {

    // set parameters for the access point
    const char *ssid = "anticipate_wifi";
    const char *password = "anticipate123";

    // start the access point
    cyw43_arch_enable_ap_mode(ssid, password, CYW43_AUTH_WPA2_MIXED_PSK);
    printf("PicoAP: Wifi Access Point started with SSID: %s\n", ssid);

    return 0;
}

int Pico_AP::stop_ap() {

    cyw43_arch_disable_ap_mode();
    printf("PicoAP: Wifi Access Point stopped\n");

    return 0;
}

#endif // PICO_AP_H