#include <Arduino.h>

// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

#include "events.h"

const int CS =  10;
const int DC =  9;
const int RST = 8;

TFT TFTscreen = TFT(CS, DC, RST);


events event;

void setup() {
  Serial.begin(115200);

  event.init();
}

void loop() {
  event.update();

  if (event.down == true)
  {
    Serial.println("Down Pressed");
  }
  if (event.left == true)
  {
    Serial.println("Left Pressed");
  }
  if (event.right == true)
  {
    Serial.println("Right Pressed");
  }
  if (event.up == true)
  {
    Serial.println("Up Pressed");
  }
  
}

