#include "task_buzzer.h"

Buzzer::Melody_t melody = {
    .nbNotes = 2,
    .duration = {500, 500},
    .frequency = {A5_NOTE_FREQ, F5_NOTE_FREQ}
};

Buzzer buzzer;

void InitBuzzer(){
    buzzer.init(ActuatorConfig::buzzerPin);
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

void BuzzerCO2DetectedControl(const JsonVariantConst& variant) {
    buzzerState.status = variant["CO2Detected"].as<bool>();
    LogUpdate("Buzzer status", "updated to", String(buzzerState.status).c_str(), "");
}