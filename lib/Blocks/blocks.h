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

const points_2d S_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 1}, {1, 0}, {1, 1}, {2, 0}
};
const points_2d S_BLOCK_MID = {1,1};


const points_2d I_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 1}, {1, 1}, {2, 1}, {3, 1}
};
const points_2d I_BLOCK_MID = {3,3};

const points_2d T_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 1}, {1, 1}, {1, 0}, {2, 1}
};
const points_2d T_BLOCK_MID = {1,1};

const points_2d Z_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 0}, {1, 0}, {1, 1}, {2, 1}
};
const points_2d Z_BLOCK_MID = {1,1};

const points_2d J_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 0}, {0, 1}, {1, 1}, {2, 1}
};
const points_2d J_BLOCK_MID = {1,1};

const points_2d O_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {1, 0}, {2, 0}, {1, 1}, {2, 1}
};
const points_2d O_BLOCK_MID = {2,1};

const points_2d L_BLOCK_HIT_BOX[HIT_BOX_SIZE] = {
    {0, 1}, {1, 1}, {2, 1}, {2, 0}
};
const points_2d L_BLOCK_MID = {1,1};

/*
Defines a transformation matrix
| 0  -1 |
| 1   0 |
*/
const vector_2d ROTATION_MATRIX_90[2] = {{0, 1}, {-1, 0}};

class blocks_entity
{
    private:
        box_shapes shape;
        colours colour;
        rotation_states rotation;
        points_2d middle;
        points_2d hit_box[HIT_BOX_SIZE];

        points_2d calculate_rotation(points_2d input)
        {
            points_2d output;
            if (shape == ISHAPE)
            {
                input.x *= 2;
                input.y *= 2;
            }
            
            output.x = ROTATION_MATRIX_90[0].i * (input.x - middle.x) + ROTATION_MATRIX_90[1].i * (input.y - middle.y);
            output.y = ROTATION_MATRIX_90[0].j * (input.x - middle.x) + ROTATION_MATRIX_90[1].j * (input.y - middle.y);
            output.x += middle.x;
            output.y += middle.y; 
            
            if (shape == ISHAPE)
            {
                output.x /= 2;
                output.y /= 2;
            }
            
            return output;
        }
    
    public:
        points_2d coordinates;
        
        blocks_entity(box_shapes shape, colours colour, const points_2d hit_box[HIT_BOX_SIZE], const points_2d mid)
        {
            coordinates.x = 0;
            coordinates.y = 0;

            rotation = NEUTRAL_ROTATE;
            this->shape = shape;
            this->colour = colour;
            middle = mid;

            for (int row = 0; row < HIT_BOX_SIZE; row++)
            {
                this->hit_box[row] = hit_box[row];
            }
        }

        blocks_entity()
        {
            coordinates.x = 0;
            coordinates.y = 0;
            rotation = NEUTRAL_ROTATE;
        }

        void rotate(grid_entity &grid)
        {
            if (shape == OSHAPE)
            {
                return;
            }

            switch (rotation)
            {
            case NEUTRAL_ROTATE:
                replace(grid);
                for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
                {
                    hit_box[i] = calculate_rotation(hit_box[i]);
                }
                render(grid);
                rotation = LEFT_ROTATE; 
                
            break;
            case LEFT_ROTATE:
                replace(grid);
                for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
                {
                    hit_box[i] = calculate_rotation(hit_box[i]);
                }
                render(grid);

                rotation = INVERT_ROTATE;
            break;
            case INVERT_ROTATE:
                replace(grid);
                for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
                {
                    hit_box[i] = calculate_rotation(hit_box[i]);
                }
                render(grid);
                
                rotation = RIGHT_ROTATE;
            break;
            case RIGHT_ROTATE:
                replace(grid);
                for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
                {
                    hit_box[i] = calculate_rotation(hit_box[i]);
                }
                render(grid);
                rotation = NEUTRAL_ROTATE;

            break;
            
            default:
                break;
            }
        }

        void move_right(grid_entity &grid)
        {
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {

                points_2d checker;
                checker.x = coordinates.x + hit_box[i].x + 1;
                checker.y = coordinates.y + hit_box[i].y;
                
                if (grid.occupied(checker))
                {
                    return;
                }
                if (grid.within_bounds(checker) == false)
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
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {
                points_2d checker;
                checker.x = coordinates.x + hit_box[i].x - 1;
                checker.y = coordinates.y + hit_box[i].y;

                if (grid.occupied(checker))
                {
                    return;
                }
                if (grid.within_bounds(checker) == false)
                {
                    return;
                }
            }
            
            replace(grid);
            coordinates.x -= 1;
            render(grid);
            return;
        }

        bool move_down(grid_entity &grid)
        {
            for (int i = 0; i < HIT_BOX_SIZE; i++)
            {
                points_2d checker;
                checker.x = coordinates.x + hit_box[i].x;
                checker.y = coordinates.y + hit_box[i].y + 1;

                if (grid.occupied(checker))
                {
                    return false;
                }
                if (grid.within_bounds(checker) == false)
                {
                    return false;
                }
            }

            replace(grid);
            coordinates.y += 1;
            render(grid);

            return true;
        }

        void update_type(box_shapes shape, colours colour, const points_2d hit_box[HIT_BOX_SIZE], const points_2d mid)
        {
            this->shape = shape;
            this->colour = colour;
            middle = mid;
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                this->hit_box[row] = hit_box[row];
            }
        }

        void render(grid_entity &grid)
        {
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                points_2d point;
                point.x = grid.offset.x + (coordinates.x + hit_box[row].x) * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                point.y = grid.offset.y + (coordinates.y + hit_box[row].y) * (CELL_SIZE + LINE_WIDTH);
                render_rect(point, CELL_SIZE, CELL_SIZE, colour);
            }
        }

        void replace(grid_entity &grid)
        {
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                points_2d point;
                point.x = grid.offset.x + (coordinates.x + hit_box[row].x) * (CELL_SIZE + LINE_WIDTH) + LINE_WIDTH;
                point.y = grid.offset.y + (coordinates.y + hit_box[row].y) * (CELL_SIZE + LINE_WIDTH);
                render_rect(point, CELL_SIZE, CELL_SIZE, COLOUR_BLACK);
            }

        }
};

blocks_entity random_block();

#endif