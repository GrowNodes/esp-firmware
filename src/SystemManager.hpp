#include "Arduino.h"
#include <ESP8266WiFi.h>

#include <GrowManager.hpp>

class SystemManager
{
	private:
		GrowManager grow_manager;
  public:
    SystemManager();
    void loop();
		void setup();
};
