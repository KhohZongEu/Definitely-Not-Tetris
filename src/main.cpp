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

uint16_t calculate_score(uint8_t consequtive_rows)
{
    if (consequtive_rows == 1)
    {
        return consequtive_rows * 100;
    }
    else if (consequtive_rows == 2)
    {
        return consequtive_rows * 300;
    }
    else if (consequtive_rows == 3)
    {
        return consequtive_rows * 500;
    }
    else 
    {
        return consequtive_rows * 800;
    }
}

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
  blocks_entity blocks[4];

  for (uint8_t i = 0; i < 4; i++)
  {
      blocks[i] = random_block();
  }
  uint8_t current_block = 0;
  uint16_t score = 0;

  grid.render_lines();
  // grid.render(blocks[current_block].coordinates, blocks[current_block].hit_box);
  blocks[current_block].render(grid);

  Serial.println("Setup Complete!!");
  Serial.println("Entering Loop");
  
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
        blocks[current_block].rotate(grid);
        last_side_movement = millis();
      }
      
    break;
    case LEFT:
      Serial.println("Left Pressed");
      if (millis() - last_side_movement > SIDE_DELAY)
      {
        blocks[current_block].move_left(grid);
        last_side_movement = millis();
      }
      
    break;
    case RIGHT:
      Serial.println("Right Pressed");
      if (millis() - last_side_movement > SIDE_DELAY)
      {
        blocks[current_block].move_right(grid);
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
      if (blocks[current_block].move_down(grid) == false)
      {
        blocks[current_block].lock_block(grid);
        
        current_block++;

        blocks[current_block - 1] = random_block();
      }
      
      if (current_block >= 4)
      {
          current_block = 0;
      }

      uint8_t full_rows = grid.check_rows();
      score += calculate_score(full_rows);
      last_down_movement = millis();
    }

  }
}

void loop() {
  
}

