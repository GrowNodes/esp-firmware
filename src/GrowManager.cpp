// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>

// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
grow_light(), exhaust_fan()
{
  growManagerSetupRan = false;
}

void GrowManager::setup() {
  Serial << "GrowManager::setup()" << endl;
  grow_light.setup();
  exhaust_fan.setup();
}

void GrowManager::loop(GrowSettings grow_settings, SensorManager sensors) {
  if (timeStatus() != timeSet || grow_settings.get_aborted()) {
    return;
  }
  // need to run after homie setup to send off values on bootup
  if (!growManagerSetupRan) {
    growManagerSetupRan = true;
    setup();
  }

  grow_light.loop(grow_settings);
  exhaust_fan.loop(grow_settings, sensors);
}
