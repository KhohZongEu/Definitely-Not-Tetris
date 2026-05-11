#ifndef BLOCKS_H
#define BLOCKS_H

#include <Arduino.h>
#include "grid.h"
#include "graphics.h"

const int HIT_BOX_SIZE = 4;

enum box_shapes
{
    ISHAPE,
    LSHAPE,
    TSHAPE,
    OSHAPE,
    ZSHAPE,
    JSHAPE,
    SSHAPE
};

enum rotation_states
{
    NEUTRAL_ROTATE,
    LEFT_ROTATE,
    INVERT_ROTATE,
    RIGHT_ROTATE
};

const grid_states S_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { BLACK, GREEN, GREEN, BLACK},
    { GREEN, GREEN, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK}
};
  
const grid_states I_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { CYAN, CYAN, CYAN, CYAN},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK}
};

const grid_states T_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { BLACK, PURPLE, BLACK, BLACK},
    { PURPLE, PURPLE, PURPLE, BLACK},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK}
};

const grid_states Z_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { RED, RED, BLACK, BLACK},
    { BLACK, RED, RED, BLACK},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK}
};

const grid_states J_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { BLACK, BLUE, BLACK, BLACK},
    { BLACK, BLUE, BLACK, BLACK},
    { BLACK, BLUE, BLACK, BLACK},
    { BLUE, BLUE, BLACK, BLACK}
};

const grid_states O_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { YELLOW, YELLOW, BLACK, BLACK},
    { YELLOW, YELLOW, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK},
    { BLACK, BLACK, BLACK, BLACK}
};

const grid_states L_BLOCK_HIT_BOX[HIT_BOX_SIZE][HIT_BOX_SIZE] = 
{
    { ORANGE, BLACK, BLACK, BLACK},
    { ORANGE, BLACK, BLACK, BLACK},
    { ORANGE, BLACK, BLACK, BLACK},
    { ORANGE, ORANGE, BLACK, BLACK}
};

class blocks_entity
{
    private:
        box_shapes shape;
        colours colour;
    
    public:
        points_2d coordinates;
        rotation_states rotation;
        grid_states hit_box[HIT_BOX_SIZE][HIT_BOX_SIZE];
        
        blocks_entity(box_shapes shape, colours colour, const grid_states hit_box[HIT_BOX_SIZE][HIT_BOX_SIZE])
        {
            coordinates.x = 0;
            coordinates.y = 0;

            rotation = NEUTRAL_ROTATE;
            this->shape = shape;
            this->colour = colour;
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                for (uint8_t col = 0; col < HIT_BOX_SIZE; col++)
                {
                    this->hit_box[row][col] = hit_box[row][col];
                }
            }
        }

        blocks_entity()
        {
            coordinates.x = 0;
            coordinates.y = 0;
            rotation = NEUTRAL_ROTATE;
        }

        void move_right(grid_entity &grid)
        {
            points_2d checker;
            checker.x = coordinates.x + 1;
            checker.y = coordinates.y;

            if (grid.occupied(checker))
            {
                return;
            }
            if (grid.within_bounds_x(coordinates.x + HIT_BOX_SIZE + 1) == true)
            {
                replace(grid);
                coordinates.x += 1;
                render(grid);
                return;
            }
            uint8_t current_last_column = MAX_CELLS_X - coordinates.x - 1;

            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                if (hit_box[row][current_last_column] != BLACK)
                {
                    return;
                }
            }
            replace(grid);
            coordinates.x += 1;
            render(grid);
        }
        
        void move_left(grid_entity &grid)
        {
            points_2d checker;
            checker.x = coordinates.x -1;
            checker.y = coordinates.y;
            if (grid.occupied(checker))
            {
                return;
            }

            if (coordinates.x > 0)
            {
                replace(grid);
                coordinates.x -= 1;
                render(grid);
                return;
            }
        }

        bool move_down(grid_entity &grid)
        {
            points_2d checker;
            checker.x = coordinates.x;
            checker.y = coordinates.y - 1;
            if (grid.occupied(checker))
            {
                return false;
            }

            if (grid.within_bounds_y(coordinates.y + HIT_BOX_SIZE + 1) == true)
            {
                replace(grid);
                coordinates.y += 1;
                render(grid);
                return true;
            }

            int current_last_row = MAX_CELLS_Y - coordinates.y - 1;

            for (uint8_t col = 0; col < HIT_BOX_SIZE; col++)
            {
                if (hit_box[current_last_row][col] != BLACK)
                {
                    return false;
                }
            }

            replace(grid);
            coordinates.y += 1;
            render(grid);

            return true;
        }

        void update_type(box_shapes shape, colours colour, const grid_states hit_box[HIT_BOX_SIZE][HIT_BOX_SIZE])
        {
            this->shape = shape;
            this->colour = colour;
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                for (uint8_t col = 0; col < HIT_BOX_SIZE; col++)
                {
                    this->hit_box[row][col] = hit_box[row][col];
                }
            }
        }

        void render(grid_entity &grid)
        {
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                for (uint8_t col = 0; col < HIT_BOX_SIZE; col++)
                {
                    if (hit_box[row][col] != BLACK)
                    {
                        points_2d point;
                        point.x = grid.offset.x + (coordinates.x + col) * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                        point.y = grid.offset.y + (coordinates.y + row) * (CELL_SIZE + LINE_WIDTH);
                        render_rect(point, CELL_SIZE, CELL_SIZE, colour);
                    }
                }
            }
        }

        void replace(grid_entity &grid)
        {
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                for (uint8_t col = 0; col < HIT_BOX_SIZE; col++)
                {
                    if (hit_box[row][col] != BLACK)
                    {
                        points_2d point;
                        point.x = grid.offset.x + (coordinates.x + col) * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                        point.y = grid.offset.y + (coordinates.y + row) * (CELL_SIZE + LINE_WIDTH);
                        render_rect(point, CELL_SIZE, CELL_SIZE, COLOUR_BLACK);
                    }
                }
            }
        }
};

blocks_entity random_block();

#endif