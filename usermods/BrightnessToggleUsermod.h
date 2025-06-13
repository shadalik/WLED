#pragma once
#include "wled.h"

class BrightnessToggleUsermod : public Usermod {
private:
  bool increase = true;
  unsigned long lastPress = 0;

public:
  void setup() {
    pinMode(0, INPUT_PULLUP); // кнопка на GPIO0
  }

  void loop() {
    if (digitalRead(0) == LOW) {
      if (millis() - lastPress > 500) { // антидребезг
        if (increase) {
          bri = min(255, bri + 25);
        } else {
          bri = max(0, bri - 25);
        }
        increase = !increase; // смена направления
        lastPress = millis();
        colorUpdated(CALL_MODE_BUTTON);
      }
    }
  }
};
