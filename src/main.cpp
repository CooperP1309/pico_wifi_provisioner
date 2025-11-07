#include "pico/cyw43_arch.h"     // wifi chip library
#include "pico/stdlib.h"         // standard library pico functions
#include "dhcpserver.h"          // pico DHCP server functionality (targeteted in CMakeLists.txt)
#include "lwip/ip4_addr.h"       // for ip4_addr_t
#include "pico_hal.h"            // pico file system lib
#include "stdinit.h"             // stdio init wrapper that clears vt terminal

#include "wifi_provisioner.h"    // actual provisioner implementation

int main() {

   // pre-initialization of cyw34 chip and stdio assumed in all classes
   stdio_init();
   cyw43_arch_init();

   // wait to ensure serial usb output is fully initialize
   sleep_ms(2000);
   printf("\nAnticipate starting...\n");

   // initialize wifi provisioning
   Wifi_Provisioner provisioner;

   if(!provisioner.has_credentials() || provisioner.btn_selected()) {
      //provisioner.start_provision();
   }

    return 0;
}