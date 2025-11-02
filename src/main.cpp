// pico sdk headers
#include "pico/cyw43_arch.h"    // wifi chip library
#include "pico/stdlib.h"        // standard library pico functions
#include "dhcpserver.h"         // pico DHCP server functionality (targeteted in CMakeLists.txt)
#include "lwip/ip4_addr.h"      // for ip4_addr_t

// project headers
#include "wifiProvision.h"

using namespace std;

int main() {

   // each class assumes standard input and wifi chip pre-initialization
   stdio_init_all();
   cyw43_arch_init();

   // wait to ensure serial usb output is fully initialize
   sleep_ms(2000);
   printf("\nAnticipate starting...\n");

   // initialize wifi provisioning
   WifiProvisioner provisioner;

   if(!provisioner.hasCredentials() || provisioner.btnSelected()) {
      //provisioner.startProvision();
   }

    return 0;
}