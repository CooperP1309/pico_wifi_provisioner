#ifndef WIFI_PROVISIONER_H
#define WIFI_PROVISIONER_H

#include <stdbool.h>

#define CREDENTIALS_PATH "wifi_credentials.txt"

// Initialize all pico io cases
//
// Initializing of stdio, the cyw34 wifi chip and the mounting of
// a pico flash file system is carried out.
int pico_prov_init();

// Returns true if the credentials aren't empty
//
// Comparing the first element of the global credentials buffer
// with "\0". I.e. the case for an empty string is false given
// credentials buffer [0] != "\0";
bool pico_prov_has_credentials();

// Reads from GPIO for button pressed
//
// Assumes gpio pins (x,y,z).
// Changing this will be simplified in later fixes
bool pico_prov_button_pressed();

// Begins wifi access point
//
// Activates the AP on the cyw34 chip and begins a listening
// dhcp server.
int pico_prov_ap_begin();

// Blinks the LED
//
// Using the cyw34 GPIO connection to led, execute a blink for int ms.
void blink(int);

#endif // WIFI_PROVISIONER_H