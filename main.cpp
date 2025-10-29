#include <iostream>
#include <string>
#include "pico/cyw43_arch.h"    // pico access point functionality
#include "pico/stdlib.h"        // standard pico functions
#include "dhcpserver.h"         // pico DHCP server functionality (targeteted in CMakeLists.txt)
#include "lwip/ip4_addr.h"      // for ip4_addr_t

#include "blink.h"              // project headers
#include "wifiProvision.h"

using namespace std;

int main() {

   // each class assumes standard input and wifi chip pre-initialization
   stdio_init_all();
   cyw43_arch_init();

   // initialize wifi provisioning
   WifiProvisioner provisioner;

   if(!provisioner.hasCredentials() || provisioner.btnSelected()) {
      provisioner.startProvision();
   }

    return 0;
}