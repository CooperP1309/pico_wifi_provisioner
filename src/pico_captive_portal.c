// library headers
#include <stdio.h>
#include "pico/stdlib.h"        // sleep_ms, stdio...
#include "pico/cyw43_arch.h"    // wifi chip library
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

// project headers
#include "pico_captive_portal.h"

// defining of http page
const char *body =
    "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>Login</title>"
    "<style>"
    "body{margin:0;font-family:Arial;background:#e9eef3;display:flex;justify-content:center;align-items:center;height:100vh;}"
    ".box{background:#fff;padding:30px;border-radius:10px;box-shadow:0 4px 10px rgba(0,0,0,.1);width:280px;}"
    ".box h2{text-align:center;margin:0 0 20px;color:#333;font-size:20px;}"
    ".full{width:100%;box-sizing:border-box;}"
    ".box input{padding:10px;margin:8px 0;border:1px solid #ccc;border-radius:6px;font-size:14px;}"
    ".box button{padding:10px;border:none;border-radius:6px;background:#007bff;color:#fff;font-size:15px;font-weight:bold;cursor:pointer;}"
    ".box button:hover{background:#0056b3;}"
    "</style></head>"
    "<body><div class=\"box\">"
    "<h2>Anticipate - Wi-Fi Login</h2>"
    "<form method=\"post\">"
    "<input class=\"full\" type=\"text\" name=\"wifi\" placeholder=\"Enter SSID\">"
    "<div style=\"position:relative\">"
    "<input class=\"full\" type=\"password\" name=\"password\" placeholder=\"Enter password\">"
    "<span style=\"position:absolute;right:5px;top:50%;transform:translateY(-50%);font-size:12px;color:#555\">*Optional</span>"
    "</div>"
    "<button class=\"full\" type=\"submit\">Login</button>"
    "</form>"
    "</div></body></html>";

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
    tcp_recv(client_pcb, pico_captive_portal_recv);
    //tcp_poll(client_pcb, tcp_server_poll, POLL_TIME_S * 2);
    //tcp_err(client_pcb, tcp_server_err);

    return pico_captive_portal_send_data(arg, captive_server->client_pcb);
    //return 0;
}

err_t pico_captive_portal_send_data(void *arg, struct tcp_pcb *client_pcb) {

    portal_server_t *captive_server = (portal_server_t*)arg;
    
    // initializing header
    int body_len = strlen(body);
    char header[256];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n", body_len);

    memcpy(captive_server->buffer_sent, body, body_len);

    captive_server->sent_len = 0;
    printf("[pico_captive_portal] writing %d bytes to client\n", (header_len + body_len));

    cyw43_arch_lwip_check();

    tcp_write(client_pcb, header, header_len, TCP_WRITE_FLAG_COPY);
    tcp_write(client_pcb, body, body_len, TCP_WRITE_FLAG_COPY);

    return ERR_OK;
}

err_t pico_captive_portal_sent(void *arg, struct tcp_pcb *tpcb, u16_t len) {

    printf("[pico_captive_portal] successfully sent http frame\n");

    return 0;
}

err_t pico_captive_portal_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {

        portal_server_t *state = (portal_server_t*)arg;
    if (!p) {
        return -1;
    }
    
    cyw43_arch_lwip_check();
    if (p->tot_len > 0) {
        printf("tcp_server_recv %d/%d err %d\n", p->tot_len, state->recv_len, err);

        // Receive the buffer
        const uint16_t buffer_left = BUF_SIZE - state->recv_len;
        state->recv_len += pbuf_copy_partial(p, state->buffer_recv + state->recv_len,
                                             p->tot_len > buffer_left ? buffer_left : p->tot_len, 0);
        tcp_recved(tpcb, p->tot_len);
    }
    pbuf_free(p);

    printf("[pico_captive_portal] recieved bufer: %s", state->buffer_recv);

    // Have we have received the whole buffer
    if (state->recv_len == BUF_SIZE) {

        // check it matches
        if (memcmp(state->buffer_sent, state->buffer_recv, BUF_SIZE) != 0) {
            printf("buffer mismatch\n");
            return -1;
        }
        printf("tcp_server_recv buffer ok\n");

        // Test complete?
        state->run_count++;
        if (state->run_count >= 5) {
            return ERR_OK;
        }

        // Send another buffer
        return pico_captive_portal_send_data(arg, state->client_pcb);
    }
    return ERR_OK;
}