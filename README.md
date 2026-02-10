<h1>Wifi Provisioning for the Raspberry Pico Pi W</h1>

<h2>About</h2>

A deployment-ready software module for IoT projects on the Raspberry Pi Pico. To acheive a working captive portal, this project integrates a DHCP server. 
Once credentials are recieved from a user, flash storage is then used to access/store credentials for future use. 

<h2>How To Build</h2>

To build this project, you must have the pico-sdk installed properly.

IF: You're building from a raspberry Pi (as a PC to develop on) use the following setup script:
https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh

IF: You're building from a linux environment see page 32 "Manually Configure your Environment":
https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline

<h2>Example Project that Uses this Module</h2>

This module is currently used in my IoT project 'Anticipate'. You can see how this module is used under 'anticipate\pico\wifi_provisioner':
https://github.com/spham52/anticipate

<h2>Psuedo Code</h2>

WIFI PROVISIONING:

    initialize littleFS instance
    read wifi credentials file
  
    If no wifi credentials saved to file, begin provisioning {
    
      start access point
      start dhcp server
      
      when user connects {
        begin captive http portal 
      }

      write provisioned credentials to pico board
      restart board
    }

CAPTIVE HTTP PORTAL:

    listen for localhost get request
    once recieved, handle client {
      send portal page html
      hold for reply
      POST-REDIRECT-GET transaction with data
    }
