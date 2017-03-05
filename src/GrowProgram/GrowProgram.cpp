// Central starting point for all Grow subsystems.
#include "GrowProgram/GrowProgram.hpp"

// Constructor - creates a GrowProgram
// and initializes the member variables and state
GrowProgram::GrowProgram() :
grow_errors(),
grow_light(),
// exhaust_fan(),
// air_pump(),
water_pump()
{
}

void GrowProgram::setup() {
  grow_light.setup();
  // exhaust_fan.setup();
  // air_pump.setup();
  water_pump.setup();
}

void GrowProgram::uploadCurrentState() {
  grow_errors.uploadCurrentState();
  grow_light.uploadCurrentState();
  // exhaust_fan.uploadCurrentState();
  // air_pump.uploadCurrentState();
  water_pump.uploadCurrentState();
}

void GrowProgram::loop() {
  grow_errors.loop();
  grow_light.loop(grow_errors);
  // exhaust_fan.loop();
  water_pump.loop();
}
