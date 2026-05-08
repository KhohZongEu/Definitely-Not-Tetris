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
            for (int i = 0; i < HIT_BOX_SIZE; i++)
            {
                for (int j = 0; j < HIT_BOX_SIZE; j++)
                {
                    this->hit_box[i][j] = hit_box[i][j];
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
            if (grid.within_bounds_x(coordinates.x + 4 * (CELL_SIZE + LINE_WIDTH)) == true)
            {
                vector_2d direction = {CELL_SIZE + LINE_WIDTH, 0};
                move_rect(coordinates, direction, colour);
                return;
            }
        }
        
        void move_left(grid_entity &grid)
        {
            if (grid.within_bounds_x(coordinates.x - (CELL_SIZE + LINE_WIDTH)) == true)
            {
                vector_2d direction = {-(CELL_SIZE + LINE_WIDTH), 0};
                move_rect(coordinates, direction, colour);
                return;
            }
        }

        void update_type(box_shapes shape, colours colour, const grid_states hit_box[HIT_BOX_SIZE][HIT_BOX_SIZE])
        {
            this->shape = shape;
            this->colour = colour;
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {
                for (uint8_t j = 0; j < HIT_BOX_SIZE; j++)
                {
                    this->hit_box[i][j] = hit_box[i][j];
                }
            }
        }

        void render()
        {
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {
                for (uint8_t j = 0; j < HIT_BOX_SIZE; j++)
                {
                    if (hit_box[j][i] != BLACK)
                    {
                        points_2d point;
                        point.x = coordinates.x + i * (CELL_SIZE + LINE_WIDTH);
                        point.y = coordinates.y + j * (CELL_SIZE + LINE_WIDTH);
                        render_rect(point, CELL_SIZE, CELL_SIZE, colour);
                    }
                }
            }
        }
};

blocks_entity random_block();

#endif