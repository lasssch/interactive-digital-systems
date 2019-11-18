#include <Arduino.h>
#include <destinationController.h>
#include <tuple>
#include <string>

Drone droneControlled;
std::map<string, int> inputs;
std::map<string, int> outputs;

//Light output mode
bool NIGHT_MODE;
bool EMERGENCY_LAND;

//Constructor
DestinationController::DestinationController(Drone _drone, std::map<string, int> _inputs, std::map<string, int> _outputs)
    : droneControlled(_drone), inputs(_inputs), outputs(_outputs)
{
    NIGHT_MODE = false;
    EMERGENCY_LAND = false;
}

//Get the number of the pin from its type and name
int DestinationController::getIONumber(string type, string name) {
    std::map<string, int> tempDict;
    if(type == "INPUT") {
        tempDict = inputs;            
    } else if(type == "OUTPUT") {
        tempDict = outputs;
    } else {
        return -1;
    }

    for (auto& pair : tempDict)
    {
        if(pair.first == name) {
            return pair.second;
        }
    }        

    return -1;
}

//Night blink wave for light output
void DestinationController::nightBlink(int pin) {
    digitalWrite(pin, LOW);
    delay(50);
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    delay(200);
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    delay(1500);
}

//Emergency blink wave for light output
void DestinationController::emergencyBlink(int pin) {
    digitalWrite(pin, LOW);
    delay(150);
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
}

void DestinationController::addButtonListener(ButtonListener *_buttonListener) {
    buttonListener = _buttonListener; 
}

//Update function for the main loop
void DestinationController::update() {
    //Button
    if (digitalRead(this->getIONumber("INPUT", "BUTTON")) == LOW) {
        this->buttonListener->buttonPressed();
        EMERGENCY_LAND = !EMERGENCY_LAND;
    } 

    //Light sensor
    if(analogRead(this->getIONumber("INPUT", "LIGHT_SENSOR")) > 800) {
        NIGHT_MODE = false;
    } else {
        NIGHT_MODE = true;
    }

    //Light modes
    if(EMERGENCY_LAND) {
        this->emergencyBlink(this->getIONumber("OUTPUT", "GREEN_LIGHT"));
    } else if(NIGHT_MODE) {
        this->nightBlink(this->getIONumber("OUTPUT", "GREEN_LIGHT"));
    } else {
        digitalWrite(this->getIONumber("OUTPUT", "GREEN_LIGHT"), LOW);
    }
}

//Register inputs and outputs
void DestinationController::registerIO() {
    //Input
    for (auto& input : inputs)
    {
        if(input.first != "" && input.second > 0) {
            pinMode(input.second, INPUT);
        }
    }
    //Output
    for (auto& output : outputs)
    {
        if(output.first != "" && output.second > 0) {
            pinMode(output.second, OUTPUT);
        }
    }        
}
    

    
