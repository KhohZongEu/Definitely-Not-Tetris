#include <Arduino.h>

#include "events.h"
#include "graphics.h"
#include "grid.h"
#include "blocks.h"
#include "constants.h"
class game_entity
{
    private:
        uint8_t offset_x;
        uint8_t offset_y;
        blocks_entity blocks[NUM_OF_BLOCKS];
        grid_entity grid;
        uint8_t current_block;

        points_2d score_point;
        uint8_t full_row_tracker;
        const char score_header[7] = "Score:";
        char score_val_string[10] = "";
        
        const uint8_t SIDE_DELAY = 100;
        uint8_t down_delay = 250;
        
        unsigned long last_side_movement = 0;
        unsigned long last_down_movement = 0;

        bool randomized = false;
        uint8_t blocks_sequence[NUM_OF_BLOCKS];

        /**
         * Calculates the score from a line clear
         * 
         * @param consequtive_rows The number of consequtive rows cleared
         * @return int The score that corresponds to the number of rows cleared
         */
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

        /**
         * Updates the string of the score
         * 
         * @param score_val_string A pointer to the string that stores the score
         * @param score The actual score of the game
         * @return void
         */
        void update_score_string(char* score_val_string, uint32_t score)
        {
            itoa(score, score_val_string, 10);
        }

        /**
         * Updates the score on the screen
         * 
         * @param score_start The location where the score will be printed
         * @param score_val_string The string that stores the score
         * @param score The actual score of the game
         * @return void
         */
        void update_visual_score(points_2d score_start,char* score_val_string, uint32_t score)
        {
            score_start.x += 11;
            render_text(score_start, score_val_string, COLOUR_BLACK);
            update_score_string(score_val_string, score);
            render_text(score_start, score_val_string, COLOUR_WHITE);
        }

        /**
         * Randomizes the blocks sequence
         * 
         * @param void
         * @return void
         */
        void randomize_blocks()
        {
            random_block_series(blocks_sequence);

            for (uint8_t i = 0; i < NUM_OF_BLOCKS; i++)
            {
                blocks[i] = convert_series_to_block(blocks_sequence[i]);
            }
        }

        /**
         * Update the next blocks when the game is running
         * 
         * @param void
         * @return void
         */
        void update_next_blocks()
        {
            uint8_t update_index = (current_block + 5) % NUM_OF_BLOCKS;
            blocks[update_index] = convert_series_to_block(blocks_sequence[update_index]);
        }
    
    public:
        events event;
        uint32_t score;
        bool start;

        /**
         * Constructor for the game_entity class with user provided arguements
         * 
         * @param offset_x The offset of the game in the x axis
         * @param offset_y The offset of the game in the y axis
         * @return void
         */
        game_entity(uint8_t offset_x=0, uint8_t offset_y=0)
        {
            start = false;

            this->offset_x = offset_x;
            this->offset_y = offset_y;
            this->grid = grid_entity(offset_x, offset_y); 

            for (uint8_t i = 0; i < NUM_OF_BLOCKS; i++)
            {
                blocks_sequence[i] = i;
            }

            randomize_blocks();
            current_block = 0;
            
            score = 0;

            event = events();
            event.init();
            
            score_point.x = grid.width + offset_x + 5;
            score_point.y = grid.height;
        }

        /**
         * Renders the initial graphics before the game is started
         * 
         * @param void
         * @return void
         */
        void init_render()
        {
            graphics_init();
            render_text(score_point, score_header, COLOUR_WHITE);
            grid.render_lines();
            blocks[current_block].render(grid);
            update_visual_score(score_point, score_val_string, score);
        }

        /**
         * Resets the game state and values
         * 
         * @param void
         * @return void
         */
        void reset()
        {
            clear_screen();
            randomize_blocks();
            score = 0;
            init_render();
            grid.reset();
        }

        /**
         * The main game logic while the game is being played
         * 
         * @param void
         * @return void
         */
        void main_game()
        {
            event.update();

            if (blocks[current_block].check_collision({0,0},grid))
            {
                start = false;
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

                    update_next_blocks();
                }
                
                if (current_block >= NUM_OF_BLOCKS)
                {
                    current_block = 0;
                    randomized = false;
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

            if (current_block == 2 && randomized == false)
            {
                random_block_series(blocks_sequence);
                randomized = true;
            }

            if (full_row_tracker >= 10 && down_delay > 50)
            {
                full_row_tracker -= 10;
                down_delay -= 50;
            }
        }
};