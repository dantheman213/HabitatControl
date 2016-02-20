# Habitat Control #

Control a reptile terrarium lighting and heating requirements to keep your pet happy! Record and log the sensor data and set triggers for when certain conditions are met.

Some examples include:

* Turn off day/night lamps instead of using a traditional analog timer (more accurate)
* Use as an advanced thermostat with multiple temperature sensors for the warm/cool side of the reptile terrarium
* and more!

The code is built to be customizable. If you need more advanced functionality you will be able to easily add it yourself or contribute to this project. Just submit a pull request!

### Requirements ###
* Raspberry Pi 1 or 2 with case and power supply
* Small/Medium Breadboard
* 20+ Jumper wires (just in case)
* 433MHz RF receiver and transmitter
 + SMAKN® 433Mhz Rf Transmitter and Receiver Link Kit
 + http://www.amazon.com/SMAKN%C2%AE-433Mhz-Transmitter-Receiver-Arduino/dp/B00M2CUALS
* 2x temperature/humidity sensors
 + Digital Temperature and Humidity measure sensor
 + http://www.amazon.com/gp/product/B018JO5BRK
* RF controlled power outlets
 + Etekcity Wireless Remote Control Electrical Outlet Switch
 + https://www.amazon.com/gp/product/B00DQELHBS

#### Other Considerations ####
* Terrarium with a critter
* 1 or more heat lamps
* Optional: night heat lamp(s)
* Optional: viewing lamp(s)

### Getting Started ###

This project is still in active development and more information will be provided when the project is ready to be consumed by 3rd parties.

### Building Project ###
* Run "./install.sh" which will build the target applications and install them at /usr/bin on your Raspberry Pi. This includes installing the libraries below.

### Libraries Required (manual install) ###

The install script will grab these libraries for you. However, if doing a manual setup then check below.

* Make sure the following libraries have been installed:
  - WiringPi (http://wiringpi.com/download-and-install/)
    + git clone git://git.drogon.net/wiringPi
    + cd wiringPi && ./build
  - Adafruit_Python_DHT (https://github.com/adafruit/Adafruit_Python_DHT)
    + git clone https://github.com/adafruit/Adafruit_Python_DHT
    + Follow Readme.md within git repo to install library onto Pi
