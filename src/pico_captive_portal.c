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

    // declare new pcb instance for both ipv4 and ipv6
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

    portal_server_t *captive_server = (portal_server_t*)arg;
    if (err != 0 || client_pcb == NULL) {
        printf("[pico_captive_portal] error accepting connection\n");
        return -1;
    }

    printf("[pico_captive_portal] connection accepted\n");

    captive_server->client_pcb = client_pcb;

    // setting callback functions and args for send and recv of http data
    tcp_arg(client_pcb, captive_server);
    tcp_sent(client_pcb, pico_captive_portal_sent);
    //tcp_recv(client_pcb, tcp_server_recv);
    //tcp_poll(client_pcb, tcp_server_poll, POLL_TIME_S * 2);
    //tcp_err(client_pcb, tcp_server_err);

    return pico_captive_portal_send_data(arg, captive_server->client_pcb);
    //return 0;
}

err_t pico_captive_portal_send_data(void *arg, struct tcp_pcb *client_pcb) {

    portal_server_t *captive_server = (portal_server_t*)arg;
    
    // initializing of http frame        
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nHello World";
    int length = strlen(response);
    memcpy(captive_server->buffer_sent, response, length);

    captive_server->sent_len = 0;
    printf("[pico_captive_portal] writing X bytes to client\n");

    cyw43_arch_lwip_check();

    err_t err = tcp_write(client_pcb, captive_server->buffer_sent, BUF_SIZE, TCP_WRITE_FLAG_COPY);
    if (err != ERR_OK) {
        printf("[pico_captive_portal] failed to send data to client\n");
        //return tcp_server_result(arg, -1);
        return -1;
    }
    return ERR_OK;
}

err_t pico_captive_portal_sent(void *arg, struct tcp_pcb *tpcb, u16_t len) {

    printf("[pico_captive_portal] successfully sent http frame\n");

    return 0;
}