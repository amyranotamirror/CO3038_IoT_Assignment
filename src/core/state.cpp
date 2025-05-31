#include "state.h"

volatile WifiState wifiState = {false, false, 0};
volatile ThingsBoardState thingsBoardState = {false, false, 0, false, false, false, false, false, false};

volatile AirQualitySensorState airQualitySensorState = {0, NAN};
volatile LightSensorState lightSensorState = {nullptr, 0, NAN};
volatile MotionSensorState motionSensorState = {0, NAN};
volatile TempHumidSensorState tempHumidSensorState = {0, NAN, NAN};

volatile LightActuatorState lightActuatorState = {0};