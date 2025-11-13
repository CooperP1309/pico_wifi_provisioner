#ifndef WIFI_PROVISIONER_H
#define WIFI_PROVISIONER_H


#define PATH_CREDENTIALS "wifi_credentials.txt"

// Initialize all pico io cases
//
// Initializing of stdio, the cyw34 wifi chip and the mounting of
// a pico flash file system is carried out.
int wifi_provisioner_init();

// Uses path macro to extract stored credentials
//
// Reading of the flash file system given the path macro.
// Writes to passed buffer address.
// Returns bytes read.
int read_credentials();

// Blinks the LED
//
// Using the cyw34 GPIO connection to led, execute a blink for int ms.
void blink(int);

#endif // WIFI_PROVISIONER_H