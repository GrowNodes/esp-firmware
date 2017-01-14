#ifndef GROW_SETTINGS_H
#define GROW_SETTINGS_H



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>

class GrowSettingsClass
{
	private:
		// void setup();

		HomieSetting<bool> h_aborted;
		HomieSetting<long>  h_light_on_at;
		HomieSetting<long>  h_light_off_at;

		bool aborted;
		int light_on_at;
		int light_off_at;

	public:
    GrowSettingsClass();
		void setup();

		bool get_aborted();
		int get_light_on_at();
		int get_light_off_at();
};


extern GrowSettingsClass GrowSettings;

#endif
