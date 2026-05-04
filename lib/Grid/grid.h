#ifndef GRID_H
#define GRID_H

#include "graphics.h"
#include <Arduino.h>

extern const uint8_t SCREEN_WIDTH;
extern const uint8_t SCREEN_HEIGHT;

const uint8_t MAX_CELLS_X = 10;
const uint8_t MAX_CELLS_Y = 20;

enum grid_states
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    PURPLE,
    CYAN,
    YELLOW,
    ORANGE
};

class grid_entity
{
    private:
        grid_states grid[MAX_CELLS_X][MAX_CELLS_Y];
        
    public:
        grid_entity()
        {
            for (uint8_t i = 0; i < MAX_CELLS_X; i++)
            {
                for (uint8_t j = 0; j < MAX_CELLS_Y; j++)
                {
                    grid[i][j] = BLACK;
                }
            }
        }
        
        void render(uint8_t x_offset=0, uint8_t y_offset=0)
        {
            for (uint8_t i = 0; i <= MAX_CELLS_Y; i++)
            {
                points_2d start = {x_offset + 0, y_offset + (i * 7)};
                points_2d end = {x_offset + (MAX_CELLS_X * 7), y_offset + (i * 7)};
                
                render_line(start, end, COLOUR_WHITE);
            }
            for (uint8_t i = 0; i <= MAX_CELLS_X; i++)
            {
                points_2d start = {x_offset + (i * 7), y_offset + 0};
                points_2d end = {x_offset + (i * 7), y_offset + (MAX_CELLS_Y * 7)};
                
                render_line(start, end, COLOUR_WHITE);
            }
        }

        bool occupied(points_2d point)
        {
            if (grid[(uint8_t) point.x][(uint8_t) point.y] != BLACK )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};

#endif