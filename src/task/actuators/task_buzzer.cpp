#include "task_buzzer.h"

Buzzer::Melody_t melody = {
    .nbNotes = 2,
    .duration = {500, 500},
    .frequency = {A5_NOTE_FREQ, F5_NOTE_FREQ}
};
// Buzzer::Melody_t melody = {
//     .nbNotes = 8,
//     .duration = {500, 500, 500, 500, 500, 500, 500, 500},
//     .frequency = {
//         A5_NOTE_FREQ, F5_NOTE_FREQ,
//         A5_NOTE_FREQ, F5_NOTE_FREQ,
//         A5_NOTE_FREQ, F5_NOTE_FREQ,
//         A5_NOTE_FREQ, F5_NOTE_FREQ
//     }
// };

Buzzer buzzer;

void InitBuzzer(){
    buzzer.init(ActuatorConfig::buzzerPin);
    
}
bool GetBuzzerStatus() {
    return buzzerState.status;
}
void SetBuzzerStatus(bool status){
    buzzerState.status = status;
}


void TaskBuzzer(void *pvParameters){
    while(1){
        // Loop warning melody when buzzer is active
        switch(GetBuzzerStatus()){
            case ON:
                if(!buzzer.hasMelody()){
                    // Serial.println("Happy birthday to you!");
                    buzzer.setMelody(&melody);
                }
                buzzer.step();
                break;
            case OFF:
                break;
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void RPCBuzzerControl(const JsonVariantConst& variant, JsonDocument& document) {
  Serial.println("RPCBuzzerControl is called");
  const size_t jsonSize = Helper::Measure_Json(variant);
  char buffer[jsonSize];
  serializeJson(variant, buffer, jsonSize);
  Serial.println(buffer);
  alertState.status = variant.as<bool>();
  digitalWrite(ActuatorConfig::lightPin, alertState.status);
}