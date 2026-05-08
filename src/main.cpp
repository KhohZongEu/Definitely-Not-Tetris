#include <Arduino.h>

#include "events.h"
#include "graphics.h"
#include "grid.h"

const uint8_t CS =  10;
const uint8_t DC =  9;
const uint8_t RST = 8;

events event;
TFT SCREEN = TFT(CS, DC, RST);
points_2d point;
grid_entity grid(28,9);

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

  grid.render();
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
  
  move_rect(point, direction, COLOUR_GREEN);
}

