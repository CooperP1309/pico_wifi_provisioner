#ifndef WIFIPROVISION_H
#define WIFIPROVISION_H

#include "picoAP.h"
#include "picoDHCP.h"

class WifiProvisioner {
    public:
        WifiProvisioner() {

            // TODO: Implement flash file management
            // read file credentails to a global variable 
        };

        int startProvision();
    private:
        PicoAP picoAP;
        Blink led;

        bool hasCredentials();
        bool btnSeletected();
};

bool WifiProvisioner::hasCredentials() {

    // TODO:
    // Check if the credentials read from the flash file are empty (case for false)

    return true;
}

bool WifiProvisioner::btnSeletected() {

    // TODO: Implement GPIO btn
    // Check if the button is pressed at two points ~300ms apart (case for true)

    return true;
}

int WifiProvisioner::startProvision() {

    // three quick blinks to indicate start of access point
    led.blink_once_quick();
    led.blink_once_quick();
    led.blink_once_quick();

    // start the access point
    picoAP.startAP();

    // continuous slow blink to indicate access point is running (30 blinks until timeout)
    for (int i=0; i<30; i++) {
        led.blink_once();
    }

    // stop the access point after timeout
    picoAP.stopAP();

    return 0;
}

#endif // WIFIPROVISION_H