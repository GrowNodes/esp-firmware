#include <SensorManager.hpp>

SensorManagerClass::SensorManagerClass() :
waterLevelNode("waterlevel", "waterlevel"),
airTempNode("temperature", "temperature"),
air_temp_sensor(AIR_SENSOR_DHT_PIN, AIR_SENSOR_DHT)
{
  dataLastSentAt = 0;
}

SensorManagerClass SensorManager;

void SensorManagerClass::setup() {
  airTempNode.advertise("degrees");
  waterLevelNode.advertise("gallons");

  pinMode(WATER_LEVEL_PIN, INPUT);
}

void SensorManagerClass::loop() {
  if (millis() - dataLastSentAt >= SEND_STATS_INTERVAL || dataLastSentAt == 0) {
    dataLastSentAt = millis();
    float new_air_temp_f = air_temp_sensor.readTemperature(true);

    if (isnan(new_air_temp_f)) {
      Serial.println("Failed to read air_temp_sensor!");
    } else {
      air_temp_f = new_air_temp_f;

      Serial << "Temperature: " << air_temp_f << " °F" << endl;
      airTempNode.setProperty("degrees").send(String(air_temp_f));
    }

    water_level = digitalRead(WATER_LEVEL_PIN) == LOW ? 1.2 : 4.9;
    waterLevelNode.setProperty("gallons").send(String(water_level));
  }

  bool is_overheating = air_temp_f > GrowSettings.get_air_temp_high();
  Notifier.setOverheat(is_overheating);


  if (water_level < 4.5) {
    Notifier.setWaterLevelLow(true);
  } else {
    Notifier.setWaterLevelLow(false);
  }
}


float SensorManagerClass::getAirTempF() {
  return air_temp_f;
}

float SensorManagerClass::getWaterLevel() {
  return water_level;
}
