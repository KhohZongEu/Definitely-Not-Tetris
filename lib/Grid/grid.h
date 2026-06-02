#ifndef GRID_H
#define GRID_H

#include <Arduino.h>
#include "graphics.h"
#include "constants.h"

class grid_entity
{
    private:
        colours grid[MAX_CELLS_X][MAX_CELLS_Y];

        /**
         * Shifts down the rows above
         * 
         * @param start The first row where all rows above needs to be shifted down.
         * @return void
         */
        void shift_down(uint8_t start)
        {
            for (int8_t row = start; row >= 0; row--)
            {
                colours buffer[MAX_CELLS_X];
                for (uint8_t col = 0; col < MAX_CELLS_X; col++)
                {
                    points_2d point;
                    point.x = offset.x + col * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                    point.y = offset.y + row * (CELL_SIZE + LINE_WIDTH);
                    render_rect(point, CELL_SIZE, CELL_SIZE, COLOUR_BLACK);
                    
                    buffer[col] = grid[col][row - 1];
                    
                    grid[col][row] = buffer[col];
                    
                    render_rect(point, CELL_SIZE, CELL_SIZE, grid[col][row]);
                }
            }
            
            for (uint8_t col = 0; col < MAX_CELLS_X; col++)
            {
                points_2d point;
                point.x = offset.x + col * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                point.y = offset.y + 0;
                grid[col][0] = COLOUR_BLACK;
                render_rect(point, CELL_SIZE, CELL_SIZE, COLOUR_BLACK);
            }
        }

        /**
         * Checks whether a row is actually full
         * 
         * @param row The row that is being checked
         * @return bool True if the row is full, False if the row is not full
         */
        bool check_full_row(uint8_t row)
        {
            for (uint8_t col = 0; col < MAX_CELLS_X; col++)
            {
                if (grid[col][row].r == COLOUR_BLACK.r && grid[col][row].g == COLOUR_BLACK.g && grid[col][row].b == COLOUR_BLACK.b)
                {
                    return false;
                }
            }
            return true;
        }

    public:
        uint8_t width;
        uint8_t height;
        points_2d offset;

        /**
         * Checks all the rows in the grid starting from the bottom and shifts the rows down if there if a full row
         * 
         * @param void
         * @return int The number of full rows that was detected
         */
        uint8_t check_rows()
        {
            uint8_t full_rows = 0;
            
            for (int8_t row = MAX_CELLS_Y - 1; row >= 0; row--)
            {
                bool full = check_full_row(row);
                
                if (full == true)
                {
                    full_rows += 1;
                    shift_down(row);
                    row++;
                }
            }

            return full_rows;
        }

        /**
         * Updates a grid location to based on whether there is a block there
         * 
         * @param target The target location where the grid cell is to be updated
         * @param colour The colour of the grid cell needs to be
         * @return void
         */
        void update_block(points_2d target, colours colour)
        {
            grid[target.x][target.y] = colour;
        }

        /**
         * The constructor for the grid_entity class
         * 
         * @param x_offset The offset of the grid from the x axis (default = 0)
         * @param y_offset The offset of the grid from the y axis (default = 0)
         * @return void
         */
        grid_entity(uint8_t x_offset=0, uint8_t y_offset=0)
        {
            for (uint8_t i = 0; i < MAX_CELLS_X; i++)
            {
                for (uint8_t j = 0; j < MAX_CELLS_Y; j++)
                {
                    grid[i][j] = COLOUR_BLACK;
                }
            }
            offset.x = x_offset;
            offset.y = y_offset;

            width = MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH);
            height = MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH);
        }
        
        /**
         * Renders blocks that are fixed in a grid
         * 
         * @param void
         * @return void
         */
        void render_lines()
        {
            points_2d start;
            start.x = offset.x + 0;
            start.y = offset.y + (0 * (CELL_SIZE + LINE_WIDTH));
            
            points_2d end;
            end.x = offset.x + (MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH));
            end.y =  offset.y + (0 * (CELL_SIZE + LINE_WIDTH));

            render_line(start, end, COLOUR_WHITE);
            
            start.x = offset.x + 0;
            start.y = offset.y + (MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH));
            
            end.x = offset.x + (MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH));
            end.y =  offset.y + (MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH));
            
            render_line(start, end, COLOUR_WHITE);
            
            start.x = offset.x + (0 * (CELL_SIZE + LINE_WIDTH));
            start.y = offset.y + 0;
            
            end.x = offset.x + (0 * (CELL_SIZE + LINE_WIDTH));
            end.y = offset.y + (MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH));
            render_line(start, end, COLOUR_WHITE);
            
            start.x = offset.x + (MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH));
            start.y = offset.y + 0;
            
            end.x = offset.x + (MAX_CELLS_X * (CELL_SIZE + LINE_WIDTH));
            end.y = offset.y + (MAX_CELLS_Y * (CELL_SIZE + LINE_WIDTH));
            
            render_line(start, end, COLOUR_WHITE);

        }

        /**
         * Checks whether a grid coordinate is occupied
         * 
         * @param point The coordinates of the point to check
         * @return bool True if its occupied, False if its not occupied
         */
        bool occupied(points_2d point)
        {
            if (point.x >= MAX_CELLS_X || point.y >= MAX_CELLS_Y)
            {
                return true;
            }

            if (grid[point.x][point.y].r != COLOUR_BLACK.r || grid[point.x][point.y].g != COLOUR_BLACK.g || grid[point.x][point.y].b != COLOUR_BLACK.b )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * Checks whether a grid coordinate is within bounds in both the x and y axis
         * 
         * @param point The coordinates of the point to check
         * @return bool True if its within bounds, False if its out of bounds
         */
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
        
        /**
         * Checks whether a grid coordinate is within bounds in the x axis
         * 
         * @param x The x axis coordinate of the point to check
         * @return bool True if its within bounds, False if its out of bounds
         */
        bool within_bounds_x(uint8_t x)
        {
            if (x >= MAX_CELLS_X || x < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * Checks whether a grid coordinate is within bounds in the y axis
         * 
         * @param y The y axis coordinate of the point to check
         * @return bool True if its within bounds, False if its out of bounds
         */
        bool within_bounds_y(uint8_t y)
        {
            if (y >= MAX_CELLS_Y || y < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * Resets all the contents of the grid
         * 
         * @param void
         * @return void
         */
        void reset()
        {
            for (uint8_t i = 0; i < MAX_CELLS_X; i++)
            {
                for (uint8_t j = 0; j < MAX_CELLS_Y; j++)
                {
                    grid[i][j] = COLOUR_BLACK;
                }
            }
        }
};

#endif
