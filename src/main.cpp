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


  switch (event.current)
  {
  case UP:

    Serial.println("Up Pressed");

    break;
  case DOWN:

    Serial.println("Down Pressed");
  
    break;
  case LEFT:

    Serial.println("Left Pressed");
  
    break;
  case RIGHT:
    
    Serial.println("Right Pressed");
  
    break;
  
  case NONE:
    
  
    break;
  
  default:
    
    Serial.println("ERROR: Unknown event");

    break;
  }
  
}

