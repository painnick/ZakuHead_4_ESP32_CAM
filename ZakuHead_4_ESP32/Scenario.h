#ifndef Scenario_h
#define Scenario_h

#include <Arduino.h>
#include <ESP32Servo.h>

#define NOT_USE_SERIAL

typedef struct {
    int bright; // 0~255
    int angle; // -90~+90
    int delay; // ms
} Scene;

class Scenario {
public:
  Scenario(int ledPin, int servoPin, int soundSensorPin);
  void attach();
  void playScenes(const Scene*scenes, int count);
  void rorate(int target_angle, int time_spent, int time_step, int bright);
  
  void flash1();
  void scenario1();
  int breathe1(int time_spent, int time_step, int min_bright, int max_bright);
  bool isClapped();
  void resetClapped();
  void delayWithClappingCheck(unsigned long ms);
  bool waitUntilClapping(unsigned long ms);
private:
  int _ledPin;
  int _servoPin;
  int _soundSensorPin;
  Servo _servo;
  int _angle;
  bool _clapped;

  void checkClapped();
};

#endif
