#ifndef PICO_AP_H
#define PICO_AP_H

// Starts the picos access point.
//
// Simply an error checking wrapper for the enable ap function.
int start_ap();

// Ends the picos access point.
//
// Simply an error checking wrapper for the disable ap function.
int stop_ap();

#endif // PICO_AP_H