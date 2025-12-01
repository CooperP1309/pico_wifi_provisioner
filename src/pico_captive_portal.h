#ifndef PICO_CAPTIVE_PORTAL_H
#define PICO_CAPTIVE_PORTAL_H

#define TCP_PORT 80
#define BUF_SIZE 2048

typedef struct {
    struct tcp_pcb *server_pcb;
    struct tcp_pcb *client_pcb;
    bool complete;
    uint8_t buffer_sent[BUF_SIZE];
    uint8_t buffer_recv[BUF_SIZE];
    int sent_len;
    int recv_len;
    int run_count;
} portal_server_t;

// The captive portal is a TCP server that sends and recieves HTTP frames.
// Hence, we use the tcp library from the lwip stack for handling sockets.

// Initializing the tcp server.
//
// We declare a new portal server instance on the heap via calloc.
// Error if new instance failed.
static portal_server_t* pico_captive_portal_init(void);

#endif // PICO_CAPTIVE_PORTAL_H