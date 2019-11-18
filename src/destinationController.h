#include <Arduino.h>
#include <map>
#include "drone.h"

using namespace std;

class DestinationController
{
    public:

        Drone droneControlled;
        std::map<string, int> inputs;
        std::map<string, int> outputs; 
        bool NIGHT_MODE;
        bool EMERGENCY_LAND;
        DestinationController(Drone _drone, std::map<string, int> _inputs, std::map<string, int> _outputs);
        void update();
        void registerIO();
        void addButtonListener(ButtonListener *_buttonListener);

    private:
        
        ButtonListener *buttonListener;
        int getIONumber(string type, string name);
        void nightBlink(int pin);
        void emergencyBlink(int pin);

};
