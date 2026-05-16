#include <Arduino.h>

#include "events.h"
#include "graphics.h"
#include "grid.h"
#include "blocks.h"
class game_entity
{
    private:
        uint8_t offset_x;
        uint8_t offset_y;

        blocks_entity blocks[4];
        grid_entity grid;
        events event;
        int current_block;
        const unsigned long SIDE_DELAY = 100;
        const unsigned long DOWN_DELAY = 200;

        unsigned long last_down_movement = 0;
        unsigned long last_side_movement = 0;


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
    
    public:
        int score;

        game_entity(uint8_t offset_x=0, uint8_t offset_y=0)
        {
            graphics_init();
            render_line({0,0}, {50,50}, COLOUR_BLUE);

            this->offset_x = offset_x;
            this->offset_y = offset_y;
            this->grid = grid_entity(this->offset_x, this->offset_y); 
            for (int i = 0; i < 4; i++)
            {
                blocks[i] = random_block();
            }

            current_block = 0;
            score = 0;
            event.init();
            
            grid.render_lines();
            blocks[current_block].render(grid);
        }

        bool main_game()
        {
            event.update();

            if (blocks[current_block].check_collision({0,0},grid))
            {
                return false;
            }

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

            return true;
        }
};