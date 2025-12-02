// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

// project headers
#include "pico_captive_portal.h"

portal_server_t* pico_captive_portal_init(void) {

    // calloc call justified for setup process where time efficiency is low priority
    portal_server_t *captive_server = calloc(1, sizeof(portal_server_t));
    
    if (!captive_server) {
        return NULL;
    }

    return captive_server;
}

int pico_captive_portal_start(portal_server_t *captive_server) {

    // declare new pcb instance
    struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
    if (!pcb) {
        printf("[pico_captive_portal] error allocating pcb memory\n");
        return -1;
    }

    // bind web port 80 to the pcb struct
    if (tcp_bind(pcb, IP_ANY_TYPE, PORT) < 0) {
        printf("[pico_captive_portal] failed to bind port 80 to socket\n");
        return -1;
    }

    // point server pcb to address of listening tcp_pcb
    captive_server->server_pcb =  tcp_listen_with_backlog(pcb, 1);
    if (!captive_server->server_pcb) {
        printf("[pico_captive_portal] failed to listen on tcp port\n");

        if (pcb) {
            tcp_close(pcb);
        }

        return -1;
    }

    printf("[pico_captive_portal] listening on port 80\n");

    // setting callback function args + call back function
    tcp_arg(captive_server->server_pcb, captive_server);
    tcp_accept(captive_server->server_pcb, pico_captive_portal_accept);

    return 0;
}

err_t pico_captive_portal_accept(void *arg, struct tcp_pcb *client_pcb, err_t err) {

    printf("I HAVE RECIEVED A TCP CONNECTION!\n");

    portal_server_t *captive_server = (portal_server_t*)arg;
    if (err != 0 || client_pcb == NULL) {
        printf("[pico_captive_portal] accept connection failed");
        return -1;
    }

    printf("[pico_captive_portal] accept connection failed");

    captive_server->client_pcb = client_pcb;

    // setting of new arg (client_pcb must be passed as dest for tcp data)
    tcp_arg(client_pcb, captive_server);

    /*
    // setting callback function for when data is sent succcessfully
    tcp_sent(client_pcb, tcp_server_sent);

    // setting callback function for when data is recieved succcessfully
    tcp_recv(client_pcb, tcp_server_recv);

    // setting callback function for polling the tcp connection
    tcp_poll(client_pcb, tcp_server_poll, POLL_TIME_S * 2);

    // setting callback function for when data is sent succcessfully
    tcp_err(client_pcb, tcp_server_err);
    */

    return pico_captive_portal_send_data(arg, captive_server->client_pcb);
    //return 0;
}

err_t pico_captive_portal_send_data(void *arg, struct tcp_pcb *client_pcb) {


    return 0;
}