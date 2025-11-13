#ifndef BLINK_H
#define BLINK_H

// Perform initialisation
int pico_led_init(void);

// Turn the led on or off
void pico_set_led(bool led_on);

#endif // BLINK_H