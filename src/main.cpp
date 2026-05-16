#include <Arduino.h>

#include "events.h"
#include "graphics.h"
#include "grid.h"
#include "blocks.h"

const uint8_t CS =  10;
const uint8_t DC =  9;
const uint8_t RST = 8;

const uint8_t GRID_OFFSET_X = 9;
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

void update_score_string(char* score_val_string, uint16_t score)
{
  itoa(score, score_val_string, 10);
}

void update_visual_score(points_2d score_start,char* score_val_string, uint16_t score)
{
  score_start.x += 11;
  render_text(score_start, score_val_string, COLOUR_BLACK);
  update_score_string(score_val_string, score);
  render_text(score_start, score_val_string, COLOUR_WHITE);
}

void setup() 
{
  events event;
  grid_entity grid(GRID_OFFSET_X,GRID_OFFSET_Y);

  unsigned long last_down_movement = 0;
  unsigned long last_movement = 0;

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
  blocks[current_block].render(grid);
  
  points_2d score_start;
  score_start.x =  TOTAL_WIDTH + 20;
  score_start.y =  TOTAL_HEIGHT;

  char* score_heading = (char *) malloc(8 * sizeof(char));
  char* score_val_string = (char*) malloc(6 * sizeof(char));
  
  strcpy(score_heading, "Score: ");
  render_text(score_start, score_heading, COLOUR_WHITE);

  update_visual_score(score_start, score_val_string, score);

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
      if (millis() - last_movement > SIDE_DELAY)
      {
        blocks[current_block].rotate(grid);
        last_movement = millis();
      }
      
    break;
    case LEFT:
      Serial.println("Left Pressed");
      if (millis() - last_movement > SIDE_DELAY)
      {
        blocks[current_block].move_left(grid);
        last_movement = millis();
      }
      
    break;
    case RIGHT:
      Serial.println("Right Pressed");
      if (millis() - last_movement > SIDE_DELAY)
      {
        blocks[current_block].move_right(grid);
        last_movement = millis();

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
      
      if (full_rows != 0)
      {
        score += calculate_score(full_rows);
        update_visual_score(score_start, score_val_string, score);
      }
      last_down_movement = millis();
    }

  }
}

void loop()
{
  
}

