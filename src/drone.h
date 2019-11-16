#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>
#include <buttonListener.h>

using namespace std;

class Drone : public ButtonListener
{
    
    public:
        Drone();
        void connect(const char* ssid, const char* password);
        void sendMessage(string message);
        void sendCommand(string command);
        bool connected();
        bool emergency;
        bool flying;
        void update();
        void handleEmergency();
        void buttonPressed();

    private:
      void deliverPackage();
 
};