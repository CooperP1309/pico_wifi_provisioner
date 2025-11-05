#ifndef WIFI_PROVISIONER_H
#define WIFI_PROVISIONER_H

#include "blink.h"           
#include "pico_fs.h"
#include "pico_ap.h"
#include "pico_dhcp.h"

const char* wifi_credentials_path = "wifi_credentials.txt";
#define FILE_SIZE 256

class Wifi_Provisioner {
    public:
        Wifi_Provisioner() {

            // three quick flashes to indicate start up of wifi module
            led.blink_once_quick();
            led.blink_once_quick();
            led.blink_once_quick();

            printf("WifiProvisioner: initializing wifi credentials...\n");
            
            if (pico_fs.init() < 0) {
                return;
            }

            // TODO: delete when done debugging
            //char buffer[32] = "Maccas wifi";
            //pico_fs.write_file(wifi_credentials_path, buffer, FILE_SIZE);

            char buffer[FILE_SIZE] = "";
            if (pico_fs.read_file(wifi_credentials_path, buffer, FILE_SIZE) < 0) {
                return;
            }

            // manually flush buffer (limit calling frequency)
            printf("WifiProvisioner: extracted from wifi credentials file: %s\n", buffer);
            fflush(stdout);
        };

        bool has_credentials();
        bool btn_selected();
        int start_provision();
    private:
        Blink led;
        Pico_FS pico_fs;
        Pico_AP pico_ap;
};

bool Wifi_Provisioner::has_credentials() {

    // TODO:
    // Check if the credentials read from the flash file are empty (case for false)

    return true;
}

bool Wifi_Provisioner::btn_selected() {

    // TODO: Implement GPIO btn
    // Check if the button is pressed at two points ~300ms apart (case for true)

    return true;
}

int Wifi_Provisioner::start_provision() {

    // three quick blinks to indicate start of access point
    led.blink_once_quick();
    led.blink_once_quick();
    led.blink_once_quick();

    // start the access point
    pico_ap.start_ap();

    // continuous slow blink to indicate access point is running (30 blinks until timeout)
    for (int i=0; i<30; i++) {
        led.blink_once();
    }

    // stop the access point after timeout
    pico_ap.stop_ap();

    return 0;
}

#endif // WIFI_PROVISIONER_H