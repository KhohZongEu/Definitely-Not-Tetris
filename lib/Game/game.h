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
        uint8_t current_block;

        points_2d score_point;
        uint8_t full_row_tracker;
        const char score_header[8] = "Score: ";
        char score_val_string[10] = "";
        
        const uint8_t SIDE_DELAY = 100;
        uint8_t down_delay = 250;
        
        unsigned long last_side_movement = 0;
        unsigned long last_down_movement = 0;

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

        void reset_blocks()
        {
            for (uint8_t i = 0; i < 4; i++)
            {
                blocks[i] = random_block();
            }
            current_block = 0;
        }

        // void display_next_block_list()
        // {
        //     uint8_t offset = 0;
        //     if (current_block != 0)
        //     {
        //         offset = (HIT_BOX_SIZE * CELL_SIZE) * current_block;

        //         for (int8_t i = current_block -1; i >= 0; i--)
        //         {
        //             blocks[i].coordinates.x = grid.width + offset_x + 5;
        //             blocks[i].coordinates.y = (HIT_BOX_SIZE * CELL_SIZE) * i;    
        //             blocks[i].render(grid);
        //         }
        //     }
            
        //     for (uint8_t i = current_block; i < 4; i++)
        //     {
        //         blocks[i].coordinates.x = grid.width + offset_x + 5;
        //         blocks[i].coordinates.y = (HIT_BOX_SIZE * CELL_SIZE) * i + offset;
        //         blocks[i].render(grid);
        //     }
        // }
    
    public:
        events event;
        uint32_t score;
        bool start;

        game_entity(uint8_t offset_x=0, uint8_t offset_y=0)
        {
            start = false;

            this->offset_x = offset_x;
            this->offset_y = offset_y;
            this->grid = grid_entity(offset_x, offset_y); 

            reset_blocks();
            
            score = 0;

            event = events();
            event.init();
            
            score_point.x = grid.width + offset_x + 5;
            score_point.y = grid.height;
        }
        
        void init_render()
        {
            graphics_init();
            render_text(score_point, score_header, COLOUR_WHITE);
            grid.render_lines();
            blocks[current_block].render(grid);
            update_visual_score(score_point, score_val_string, score);
        }

        void reset()
        {
            clear_screen();
            reset_blocks();
            score = 0;
            init_render();
            grid.reset();
        }

        bool main_game()
        {
            event.update();

            if (blocks[current_block].check_collision({0,0},grid))
            {
                start = false;
                return false;
            }
            switch (event.button_pressed)
            {
            case UP:
                Serial.println(F("Up pressed"));
                
            break;
            case DOWN:
                Serial.println(F("Down pressed"));
                if (millis() - last_side_movement > SIDE_DELAY)
                {
                    blocks[current_block].rotate(grid);
                    last_side_movement = millis();
                }
            
            break;
            case LEFT:
                Serial.println(F("Left Pressed"));
                if (millis() - last_side_movement > SIDE_DELAY)
                {
                    blocks[current_block].move_left(grid);
                    last_side_movement = millis();
                }
            
            break;
            case RIGHT:
                Serial.println(F("Right Pressed"));

                if (millis() - last_side_movement > SIDE_DELAY)
                {
                    blocks[current_block].move_right(grid);
                    last_side_movement = millis();

                }
            
            break;
            case NONE:
            
            break;
            default:
                Serial.println(F("ERROR: Something weird happened with input"));
            
            break;
            }

            if (millis() - last_down_movement > down_delay)
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
                    full_row_tracker += full_rows;
                    update_visual_score(score_point, score_val_string, score);
                }
                last_down_movement = millis();
            }

            if (full_row_tracker >= 10 && down_delay > 50)
            {
                full_row_tracker -= 10;
                down_delay -= 50;
            }

            return true;
        }
};