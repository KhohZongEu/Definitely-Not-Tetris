#ifndef GRID_H
#define GRID_H

#include "graphics.h"
#include <Arduino.h>

extern const uint8_t SCREEN_WIDTH;
extern const uint8_t SCREEN_HEIGHT;

const uint8_t MAX_CELLS_X = 10;
const uint8_t MAX_CELLS_Y = 20;
const uint8_t CELL_SIZE = 6;
const uint8_t LINE_WIDTH = 1;


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
        points_2d offset;
        uint8_t width;
        uint8_t height;
        
    public:
        grid_entity(uint8_t x_offset=0, uint8_t y_offset=0)
        {
            for (uint8_t i = 0; i < MAX_CELLS_X; i++)
            {
                for (uint8_t j = 0; j < MAX_CELLS_Y; j++)
                {
                    grid[i][j] = BLACK;
                }
            }
            offset.x = x_offset;
            offset.y = y_offset;

            width = MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH);
            height = MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH);
        }
        
        void render()
        {
            for (uint8_t i = 0; i <= MAX_CELLS_Y; i++)
            {
                points_2d start = {offset.x + 0, offset.y + (i * (CELL_SIZE + LINE_WIDTH))};
                points_2d end = {offset.x + (MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH)), offset.y + (i * (CELL_SIZE + LINE_WIDTH))};
                
                render_line(start, end, COLOUR_WHITE);
            }
            for (uint8_t i = 0; i <= MAX_CELLS_X; i++)
            {
                points_2d start = {offset.x + (i * (CELL_SIZE + LINE_WIDTH)), offset.y + 0};
                points_2d end = {offset.x + (i * (CELL_SIZE + LINE_WIDTH)), offset.y + (MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH))};
                
                render_line(start, end, COLOUR_WHITE);
            }
        }

        bool occupied(points_2d point)
        {
            if (grid[point.x][point.y] != BLACK )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool within_bounds(points_2d point)
        {
            if (within_bounds_x(point.x) == false)
            {
                return false;
            }
            
            if (within_bounds_y(point.y) == false)
            {
                return false;
            }

            return true;
        }
        
        bool within_bounds_x(uint8_t x)
        {
            if (x > offset.x + width || x < offset.x)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        bool within_bounds_y(uint8_t y)
        {
            if (y > offset.y + height || y < offset.y)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
};

#endif