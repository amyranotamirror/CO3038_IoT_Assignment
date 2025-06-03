#include "task_buzzer.h"

Buzzer::Melody_t melody = {
    .nbNotes = 2,
    .duration = {500, 500},
    .frequency = {A5_NOTE_FREQ, F5_NOTE_FREQ}
};

Buzzer buzzer;

void InitBuzzer(){
    LogInfo("Buzzer actuator", "initializing ...");
    buzzer.init(ActuatorConfig::buzzerPin, ActuatorConfig::buzzerPWMChannel);
    LogSuccess("Buzzer actuator", "initialized successfully");
}

void TaskBuzzer(void *pvParameters){
    while(1){
        // Loop warning melody when buzzer is active
        if (buzzerState.status == ON) {
            if (!buzzer.hasMelody()) {
                buzzer.setMelody(&melody);
            }
        }
        buzzer.step();
        vTaskDelay(SystemConfig::tinyTaskDelay);
    }
}

void BuzzerCo2DetectedControl(const JsonVariantConst& variant) {
    bool newStatus = variant["co2Detected"].as<bool>();
    LogUpdate("Buzzer status", "updated to", String(newStatus).c_str(), "");
    buzzerState.status = newStatus;
}