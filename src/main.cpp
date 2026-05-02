#include <Arduino.h>

#include <SPI.h>

#include "events.h"
#include "graphics.h"

const int CS =  10;
const int DC =  9;
const int RST = 8;

events event;
TFT SCREEN = TFT(CS, DC, RST);
points_2d point;


void setup() {
  Serial.begin(115200);
  
  graphics_init();
  Serial.println("Screen Details");
  Serial.print("Width: ");
  Serial.println(SCREEN_WIDTH);
  Serial.print("Height: ");
  Serial.println(SCREEN_HEIGHT);
  
  event.init();
  point.x = 50;
  point.y = 50;
}


void loop() {
  event.update();

  vector_2d direction = {0,0};
  
  switch (event.button_pressed)
  {
    case UP:
    
    Serial.println("Up Pressed");
    
    direction.j -= 1;
    
    break;
    case DOWN:
    
    Serial.println("Down Pressed");
    
    direction.j += 1;
    
    break;
    case LEFT:
    
    Serial.println("Left Pressed");
    
    direction.i -= 1;
    
    break;
    case RIGHT:
    
    Serial.println("Right Pressed");
    direction.i += 1;
    
    break;
    
    case NONE:
    
    
    break;
    
    default:
    
    Serial.println("ERROR: Unknown event");
    
    break;
  }
  
  move_rect(point, direction, PURPLE);
}

