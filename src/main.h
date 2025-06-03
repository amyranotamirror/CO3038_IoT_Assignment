#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "core/config.h"
#include "core/state.h"
#include "core/utils.h"

#include "task/actuators/task_alert.h"
#include "task/actuators/task_buzzer.h"
#include "task/actuators/task_curtain.h"
#include "task/actuators/task_light.h"

#include "task/network/task_ota.h"
#include "task/network/task_rpc.h"
#include "task/network/task_shared_attr.h"
#include "task/network/task_telemetry.h"
#include "task/network/task_thingsboard.h"
#include "task/network/task_wifi.h"

#include "task/sensors/task_air_quality_sensor.h"
#include "task/sensors/task_light_sensor.h"
#include "task/sensors/task_presence_sensor.h"
#include "task/sensors/task_temp_humid_sensor.h"

#endif
