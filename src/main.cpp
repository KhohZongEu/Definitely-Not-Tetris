#include <Arduino.h>

#include "events.h"
#include "graphics.h"
#include "grid.h"
#include "blocks.h"

const uint8_t CS =  10;
const uint8_t DC =  9;
const uint8_t RST = 8;

const uint8_t GRID_OFFSET_X = 29;
const uint8_t GRID_OFFSET_Y = 10;

events event;
TFT SCREEN = TFT(CS, DC, RST);
grid_entity grid(GRID_OFFSET_X,GRID_OFFSET_Y);
blocks_entity block;

void setup() {
  Serial.begin(115200);

  graphics_init();
  Serial.println("Screen Details");
  Serial.print("Width: ");
  Serial.println(SCREEN_WIDTH);
  Serial.print("Height: ");
  Serial.println(SCREEN_HEIGHT);
  
  event.init();

  block.update_type(LSHAPE, COLOUR_ORANGE, L_BLOCK_HIT_BOX);

  block.coordinates.x = GRID_OFFSET_X + LINE_WIDTH;
  block.coordinates.y = GRID_OFFSET_Y;

  grid.render();
  block.render();
}

void loop() { 
  
  event.update();
  
  switch (event.button_pressed)
  {
    case UP:
    
    Serial.println("Up Pressed");
    
    break;
    case DOWN:
    
    Serial.println("Down Pressed");
    
    break;
    case LEFT:
    
    Serial.println("Left Pressed");
    block.move_left(grid);
    
    
    break;
    case RIGHT:
    
    Serial.println("Right Pressed");
    block.move_right(grid);
    
    break;
    
    case NONE:
    
    
    break;
    
    default:
    
    Serial.println("ERROR: Unknown event");
    
    break;
  }
  
}

