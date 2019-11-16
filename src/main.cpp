#include <Arduino.h>
#include <destinationController.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

Drone drone;
//Instantiate a destination controller with inputs: button and light sensor and output: green light bulb
DestinationController destCtrl = DestinationController(
  drone,
  {{"BUTTON", 23}, {"LIGHT_SENSOR", 4}},
  {{"GREEN_LIGHT", 5}}
); 

void setup() {
  Serial.begin(9600); 
  destCtrl.registerIO(); //Registering the different I/O's of the destination controller
  destCtrl.addButtonListener(&drone);
  drone.connect("TELLO-FE2EE8", "");
}

void loop() {
  destCtrl.update();  
  drone.update();
}
