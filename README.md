# Simple Smart Home Application.
This application aims to control three devices and get the humidity and temperature in your home.
this application is divided into two parts (hardware and software):
The hardware part consists of the following devices:
1- Arduino mega.
2- DHT-22 sensor. 
3- Relays.
4- breadboard. 
5- ESP-01.
6- wires.
7- heater. 
8- tow lamps.

Arduino Mega use to read the signals and perform some processing then show the result to the user, DHT-22 sensor use to get the humidity and temperature, Relays that are used to control a circuit by separate low-power signal, breadboard that allows you to build your circuit in an easy way and ESP-01 where can use it as server or client or soft-access point but in our project will use 
as a server to read the commands from the client.

The software part, we have code for ESP-01 which have the HTML Page that contains three buttons in order to send the commands and code for Arduino Mega to control the devices.

