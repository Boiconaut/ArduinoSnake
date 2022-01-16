#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "headre.h"

void setup() {
  Serial.begin(115200);
  display.begin(0x3C);
  display.clearDisplay();
  step = sizeof(Position);
  speed = 2;
  NewGame();
}
 
void loop() {
  checkButtons();
  if(millis() - timer >= 1000 / speed){
    timer = millis();
    display.clearDisplay();
    UpdateBound();
    Move();
    display.display();
  }
}
