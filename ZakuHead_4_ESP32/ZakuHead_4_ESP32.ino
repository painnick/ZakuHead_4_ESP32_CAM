#include  "Scenario.h"

#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems

#define SERVO_PIN 14
#define LED_PIN   15
#define SOUND_SENSOR_PIN 16

Scenario *scenario;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  
  scenario = new Scenario(LED_PIN, SERVO_PIN, SOUND_SENSOR_PIN);
  #ifdef USE_SERIAL
    Serial.begin(115200);
  #endif
  scenario->attach();
}

int loop_index = 0;

void loop() {
  if(loop_index == 0) {
    scenario->resetClapped();
    scenario->scenario1();
  }

  scenario->breathe1(1000, 100, 15, 195);
  if (scenario->isClapped()) {
    loop_index = 0;
  } else {
    if(scenario->waitUntilClapping(500)) {
      loop_index = 0;
    } else {
      analogWrite(LED_PIN, 127);
      if (scenario->waitUntilClapping(3000)) {
        loop_index = 0;
      } else {
        loop_index = (loop_index + 1) % 10;
      }
    }
  }
}
