#ifndef WIFI_PROVISIONER_H
#define WIFI_PROVISIONER_H

#include <stdbool.h>
#include "pico_prov_errors.h"

typedef struct {
    char ssid[33];          // up to 32 + terminating null
    char password[64];      // up to 63 + terminating null
} pico_prov_credentials_t;

#define CREDENTIALS_PATH "wifi_credentials.txt"

// Initialize all pico io cases
//
// Initializing of stdio, the cyw34 wifi chip and the mounting of
// a pico flash file system is carried out. If init suceeds, 
// reference to credentials struct is used to assign extracted
// credentials from file.
pico_prov_err_t pico_prov_init(pico_prov_credentials_t *wifi_credentials);

// Begins wifi access point
//
// Activates the AP on the cyw34 chip and begins a listening
// dhcp server.
int pico_prov_begin();

// Blinks the LED
//
// Using the cyw34 GPIO connection to led, execute a blink for int ms.
void blink(int);

#endif // WIFI_PROVISIONER_H