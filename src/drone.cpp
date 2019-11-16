#include <Arduino.h>
#ifndef DRONE_H
#include "drone.h"
#endif
#include <WiFiConnection.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

WifiConnection wifiConnection;
bool emergency;
bool flying;

Drone::Drone() {
        emergency = false;
        flying = false;
}

bool Drone::connected() {
        return wifiConnection.connected;
}

void Drone::sendMessage(string message) {
        wifiConnection.sendMessage(message);
}

void Drone::sendCommand(string command) {
        if(emergency && command == "emergency") {
                Serial.print("Executing *emergency* command: ");
                Serial.println(command.c_str());
                wifiConnection.sendCommand(command);   
                Serial.println(wifiConnection.getResponse().c_str());
                flying = false;
                delay (3000);
        } else {
                Serial.print("Executing command: ");
                Serial.println(command.c_str());
                wifiConnection.sendCommand(command);   
                Serial.println(wifiConnection.getResponse().c_str());

                if(command == "land" || command == "emergency") {
                        flying = false;
                } else if(command == "takeoff") {
                        flying = true;
                }
                delay (3000);
        }
}

void Drone::connect(const char* ssid, const char* password) {
        wifiConnection.connect(ssid, password);
}

void Drone::update() {
        if(emergency) {
                Serial.println("emergency state!");
                this->handleEmergency();
        } else {
                if(this->connected()) {
                        //Behavior
                        if(!flying) {
                                this->sendCommand("command");
                                this->sendCommand("takeoff");
                        } else {
                                this->deliverPackage();
                        }
                } else {
                        //Reconnect
                        this->connect("TELLO-FE2EE8", "");
                        this->sendCommand("command");
                }
        }
}

void Drone::handleEmergency() {
        if(emergency) {
                sendCommand("stop");
                sendCommand("land");
        }
}

void Drone::buttonPressed() {
        emergency = !emergency;
        handleEmergency();
        Serial.print("emergency: ");
        Serial.println(emergency);
}

void Drone::deliverPackage() {
        this->sendCommand("mon");
        this->sendCommand("go 0 0 50 20 m2");
        this->sendCommand("land");
        this->sendCommand("takeoff");
        this->sendCommand("cw 180");
        this->sendCommand("go 0 0 50 20 m1");
        this->sendCommand("land");
}
       

 
