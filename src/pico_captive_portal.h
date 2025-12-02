#ifndef PICO_CAPTIVE_PORTAL_H
#define PICO_CAPTIVE_PORTAL_H

#define PORT 80
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
portal_server_t* pico_captive_portal_init(void);

// Starting of the captive server listening on tcp web port 80.
//
// Declare a new pcb instance, hook it up to the IP available on the wifi chip,
// bind it to port 80 and begin listening on it. Point the server pcb pointer
// to the listening pcb instance.
int pico_captive_portal_start(portal_server_t *captive_server);

// Call back function for accepted requests
//
// Used by the lwip stack as a call back function when a connection is accepted 
// on a listening TCP socket.
err_t pico_captive_portal_accept(void *arg, struct tcp_pcb *client_pcb, err_t err);

// Sends data to an accepted connection
//
// Arg set as client pcb via tcp_arg(). This will deliver a http response with html
// and css for the captive web portal.
err_t pico_captive_portal_send_data(void *arg, struct tcp_pcb *client_pcb);

#endif // PICO_CAPTIVE_PORTAL_H