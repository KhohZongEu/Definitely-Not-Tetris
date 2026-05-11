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
TFT SCREEN = TFT(CS, DC, RST);

const unsigned long DOWN_DELAY = 200;
const unsigned long SIDE_DELAY = 100;

void setup() {
  events event;
  grid_entity grid(GRID_OFFSET_X,GRID_OFFSET_Y);

  unsigned long last_down_movement = 0;
  unsigned long last_side_movement = 0;

  Serial.begin(115200);

  graphics_init();
  Serial.println("Screen Details");
  Serial.print("Width: ");
  Serial.println(SCREEN_WIDTH);
  Serial.print("Height: ");
  Serial.println(SCREEN_HEIGHT);

  
  event.init();

  blocks_entity block = random_block();

  grid.render();
  block.render(grid);

  while (true)
  {
    event.update();

    switch (event.button_pressed)
    {
    case UP:
      Serial.println("Up Pressed");
      
    break;
    case DOWN:
      Serial.println("Down Pressed");
      if (millis() - last_side_movement > SIDE_DELAY)
      {
        block.rotate(grid);
        last_side_movement = millis();
      }
      
    break;
    case LEFT:
      Serial.println("Left Pressed");
      if (millis() - last_side_movement > SIDE_DELAY)
      {
        block.move_left(grid);
        last_side_movement = millis();
      }
      
    break;
    case RIGHT:
      Serial.println("Right Pressed");
      if (millis() - last_side_movement > SIDE_DELAY)
      {
        block.move_right(grid);
        last_side_movement = millis();

      }
      
    break;
    case NONE:
    
    break;
    
    default:
      
      Serial.println("ERROR: Unknown event");
      
    break;
    }

    if (millis() - last_down_movement > DOWN_DELAY)
    {
      block.move_down(grid);
      last_down_movement = millis();
    }

  }
}

void loop() {
  
}

