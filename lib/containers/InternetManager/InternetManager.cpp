#include "Arduino.h"
#include "../../components/Led/Led.cpp"

class InternetManager
{
	private:
	Led status_led;

  public:
		InternetManager();
		void setup();
		void loop();
};

// Constructor - creates a InternetManager
// and initializes the member variables and state
InternetManager::InternetManager() :
	status_led(D4) {}



void InternetManager::setup() {
	status_led.setMode(4);
}


void InternetManager::loop() {
	status_led.update();
}
