// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

// project headers
#include "pico_captive_portal.h"

static portal_server_t* pico_captive_portal_init(void) {

    // calloc call justified for setup process where time efficiency is low priority
    portal_server_t *server = calloc(1, sizeof(portal_server_t));
    
    if (!server) {
        return NULL;
    }

    return server;
}