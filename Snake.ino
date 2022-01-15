#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "headre.h"

void setup() {
  Serial.begin(115200);
  display.begin(0x3C);
  display.clearDisplay();
  NewGame();
}
 
void loop() {
  checkButtons();
  if(millis() - timer >= 500){
    timer = millis();
    display.clearDisplay();
    UpdateBound();
    Move();
    display.display();
  }
}
