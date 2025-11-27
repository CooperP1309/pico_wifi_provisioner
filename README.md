<h1>Wifi Provisioning for the Raspberry Pico Pi W</h1>

<h2>Building Note</h2>

Built around the Pico Pi W, not the Pico Pi W 2. Should still work, though not tested. 
To use this repo, you must have the pico-sdk downloaded. Run this setup script from Raspberry Pi 
to download it (linux terminal script): 
  
  https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh

Should you run this, this repo will gather the dependencies with no problems.

<h2>Usage Note</h2>

This is an educational project for me to learn the essentials of embedded C. Please refrain from
using this code for anything other than hobby projects.

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
    }

CAPTIVE HTTP PORTAL:

    listen for localhost get request
    once recieved, handle client {
      send portal page html
      hold for reply
      
    }