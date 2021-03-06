#include "GrowProgram/Peltier.hpp"

Peltier::Peltier():
_peltierNode("peltier_cooler", "duty cycle %")
{
	_power_state = 0;
}


	void Peltier::setup() {
		_peltierNode.advertise("pwm");
	}

void Peltier::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}

	_peltierNode.setProperty("pwm").send(String(_power_state/255.0*100));
}

	void Peltier::loop() {
		if (Sensors.air_sensor.getTemp() <= PELTIER_OFF_TEMP) {
			setState(0);
			return;
		}

		if (Sensors.air_sensor.getTemp() >= PELTIER_MAX_POWER_TEMP) {
			setState(255);
			return;
		}

		float degrees_over_ideal_temp = Sensors.air_sensor.getTemp() - PELTIER_OFF_TEMP;
		float pwmPercent = degrees_over_ideal_temp / PELTIER_INTERPOLATION_RANGE;

		setState(255*pwmPercent);
	}



	void Peltier::setState(uint8_t new_power_state) {
		if (new_power_state == _power_state) {
			return;
		}
		_power_state = new_power_state;
		uploadCurrentState();

		Wire.beginTransmission(HWC_I2C_ID);
		Wire.write(PELTIER);  // command peltier
	  Wire.write(_power_state);
	  Wire.endTransmission();

		Wire.beginTransmission(HWC_I2C_ID);
		Wire.write(PELTIER_FAN);  // command
	  Wire.write(_power_state > 0); //fans on if peltier is on
	  Wire.endTransmission();

		Serial.print("Peltier cooler at ");
		Serial.print(_power_state/255.0*100);
		Serial.println("%");
	}
