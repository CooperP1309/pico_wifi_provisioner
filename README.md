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

Linux Build Steps (sorry windows users)

Step 1. Build the project using the build script:

    In the project directory, make the build script executable by invoking 'sudo chmod +x build.sh'.
    With this done, you simply build your project by invoking './build.sh'.

Step 2. Flash the compiled code onto your Pi Pico:

    Still in the project directory, move the compiled code to your Pico device by invoking 'cp build/pico_wifi_provisiod.uf2 /media/<user>/RPI-RP2/'.

Step 3. See the output of the device (optional):

    When the cp command is done, the device will immediately start executing your code. To see the logging outputs, I use the minicom program like so:
    'minicom -D /dev/ttyACM0 -b 115200'.

    Note: Your pico output might be in a different file in /dev. ttyACM0 is the default assuming nothing else is outputting there. 
    Another Note: minicom is really fidgety to use. I only included this step for someone as clueless as me. If you can't execute commands in minicom, 
    try pressing 'enter' and it might work.

<h2>Example Project that Uses this Module</h2>

This project has 'example_main.c' in the source files which provides the most bare-bones example of the provisioner API. If you want to see how I've integrated this as a sub-module in another project however, see 'anticipate\pico\src\main.c' in my IoT project 'Anticipate': https://github.com/spham52/anticipate

The only API functions required for this module are all used in main, and are preceded by 'pico_prov_...()'

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
