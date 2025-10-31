---- Wifi Provisioning for the Raspberry Pico Pi W ----

Built around the Pico Pi W, not the Pico Pi W 2. Should still work, though not tested. 
To use, you must have the pico-sdk downloaded. Run this setup script from Raspberry Pi: 
  
  https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh

Should you run this, this repo will gather the dependencies with no problems.

---- Psuedo Code ----

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
  




  
  
