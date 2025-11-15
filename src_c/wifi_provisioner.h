#ifndef WIFI_PROVISIONER_H
#define WIFI_PROVISIONER_H


#define CREDENTIALS_PATH "wifi_credentials.txt"

// Initialize all pico io cases
//
// Initializing of stdio, the cyw34 wifi chip and the mounting of
// a pico flash file system is carried out.
int wifi_provisioner_init();

// Blinks the LED
//
// Using the cyw34 GPIO connection to led, execute a blink for int ms.
void blink(int);

#endif // WIFI_PROVISIONER_H