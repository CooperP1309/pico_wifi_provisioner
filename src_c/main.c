/*
#include "pico/cyw43_arch.h"     // wifi chip library
#include "pico/stdlib.h"         // standard library pico functions
#include "dhcpserver.h"          // pico DHCP server functionality (targeteted in CMakeLists.txt)
#include "lwip/ip4_addr.h"       // for ip4_addr_t
#include "pico_hal.h"            // pico file system lib
#include "stdinit.h"             // stdio init wrapper that clears vt terminal
*/

#include "wifi_provisioner.h"    // actual provisioner implementation

int main() {

   // initialize all necessary systems + wifi credentials
   wifi_provisioner_init();

   // 
 
    return 0;
}