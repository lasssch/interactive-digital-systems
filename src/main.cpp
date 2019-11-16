#include <Arduino.h>
#include <destinationController.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

Drone drone;
DestinationController destCtrl = DestinationController(
  drone,
  {{"BUTTON", 23}, {"LIGHT_SENSOR", 4}},
  {{"GREEN_LIGHT", 5}}
); 

void setup() {
  Serial.begin(9600); 
  destCtrl.registerIO();
  destCtrl.addButtonListener(&drone);
  drone.connect("TELLO-FE2EE8", "");
}

void loop() {
  //Destination controller
  destCtrl.update();  
  //Drone
  drone.update();
}
