#ifndef WIFIPROVISION_H
#define WIFIPROVISION_H

#include "picoAP.h"
#include "picoDHCP.h"

#define FILESYS_SIZE (256 * 1024)

static struct lfs_config *lfs_cfg;
static lfs_t lfs;

class WifiProvisioner {
    public:
        WifiProvisioner() {

            // three quick flashes to indicate start up of wifi module
            led.blink_once_quick();
            led.blink_once_quick();
            led.blink_once_quick();
            
            // initialize files and read wifi credentials
            if (mountLFS()) {
                return;
            }

        };

        int mountLFS();         // LittleFileSystem must be mounted to read and write files
        bool hasCredentials();
        bool btnSelected();
        int startProvision();
    private:
        PicoAP picoAP;
        Blink led;

};

int WifiProvisioner::mountLFS() {
    
    // we start by initializing the global lfs config instance
    lfs_cfg = pico_lfs_init(PICO_FLASH_SIZE_BYTES - FILESYS_SIZE, FILESYS_SIZE);
    /*
        note: by setting start as the total bytes - file sys size, we start at the end of flash
    */
    
    if (!lfs_cfg) {
        printf("\nWifiProvision:\n  Failed to init littleFS\n");
        return 1;
    }

    printf("\nWifiProvision:\n  littleFS initialized\n");
    
    // mount will be unsuccessfull if no file system is formatted yet
    if (lfs_mount(&lfs, lfs_cfg)) {
        
        printf("\nWifiProvision:\n  mount failed. Reformatting file system...\n");
        
        // abort if formatting fails
        if (lfs_format(&lfs, lfs_cfg)) {
            return 1;
        }
    }
    
    printf("\nWifiProvision:\n  littleFS mounted and ready for use\n");

    return 0;
}

bool WifiProvisioner::hasCredentials() {

    // TODO:
    // Check if the credentials read from the flash file are empty (case for false)

    return true;
}

bool WifiProvisioner::btnSelected() {

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
