#ifndef BLOCKS_H
#define BLOCKS_H

#include <Arduino.h>
#include "grid.h"
#include "graphics.h"
#include "constants.h"


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

class blocks_entity
{
    private:
        box_shapes shape;
        colours colour;
        rotation_states rotation;
        points_2d middle;
        points_2d hit_box[HIT_BOX_SIZE];

        /**
         * Calculates the block rotation
         * 
         * @param input The original coordinate of a block segment
         * @return points_2d The new coordinate of a block segment
         */
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

        /**
         * Updates the grid to lock a block in place
         * 
         * @param &grid A reference to the grid that the block is within 
         * @return void
         */
        void lock_block(grid_entity &grid)
        {
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {
                points_2d entity;
                entity.x = coordinates.x + hit_box[i].x;
                entity.y = coordinates.y + hit_box[i].y;
                grid.update_block(entity, colour);
            }
        }
        
        /**
         * Constructs the blocks class with specified parameters
         * 
         * @param shape The shape of the block
         * @param colour The colour of the block
         * @param hit_box[] An array of the hitbox
         * @param mid The location of the rotation point of the block
         * @return void
         */
        blocks_entity(box_shapes shape, colours colour, const points_2d hit_box[HIT_BOX_SIZE], const points_2d mid)
        {
            coordinates.x = 3;
            coordinates.y = 0;

            rotation = NEUTRAL_ROTATE;
            this->shape = shape;
            this->colour = colour;
            middle = mid;

            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                this->hit_box[row] = hit_box[row];
            }
        }

        /**
         * Default constructor of the block class
         * 
         * @param void
         * @return void
         */
        blocks_entity()
        {
            coordinates.x = 3;
            coordinates.y = 0;
            rotation = NEUTRAL_ROTATE;
        }

        /**
         * Handles what rotation state the block is in and rotates the block accordingly
         * 
         * @param void
         * @return void
         */
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

        /**
         * Checks whether the block is going to collide with either the wall or another block
         * 
         * @param direction The direction the block needs to travel in a vector
         * @param &grid The reference the the grid the block is in
         * @return bool True when there is a collision, False when there is no collision
         */
        bool check_collision(vector_2d direction, grid_entity &grid)
        {
            for (uint8_t i = 0; i < HIT_BOX_SIZE; i++)
            {
                points_2d checker;
                checker.x = coordinates.x + hit_box[i].x + direction.i;
                checker.y = coordinates.y + hit_box[i].y + direction.j;

                if (grid.occupied(checker))
                {
                    return true;
                }
                if (grid.within_bounds(checker) == false)
                {
                    return true;
                }
            }

            return false;
        }

        /**
         * Moves the block to the right if a valid move is detected
         * 
         * @param &grid The reference to the grid the block is in
         * @return void
         */
        void move_right(grid_entity &grid)
        {
            vector_2d direction;
            direction.i = 1;
            direction.j = 0;

            if (check_collision(direction, grid) == true)
            {
                return;
            }
                
            replace(grid);
            coordinates.x += 1;
            render(grid);
        }
        
        /**
         * Moves the block to the left if a valid move is detected
         * 
         * @param &grid The reference to the grid the block is in
         * @return void
         */
        void move_left(grid_entity &grid)
        {
            vector_2d direction;
            direction.i = -1;
            direction.j = 0;
            
            if (check_collision(direction, grid) == true)
            {
                return;
            }
            
            replace(grid);
            coordinates.x -= 1;
            render(grid);
        }

        /**
         * Moves the block to the down if a valid move is detected
         * 
         * @param &grid The reference to the grid the block is in
         * @return bool True when the block is moved down, False when the block can't move down
         */
        bool move_down(grid_entity &grid)
        {
            vector_2d direction;
            direction.i = 0;
            direction.j = 1;
            
            if (check_collision(direction, grid) == true)
            {
                return false;
            }

            replace(grid);
            coordinates.y += 1;
            render(grid);

            return true;
        }

        /**
         * Updates the contents of the block with provided arguements
         * 
         * @param shape The shape of the block
         * @param colour The colour of the block
         * @param hit_box[] An array of the hitbox
         * @param mid The location of the rotation point of the block
         * @return void
         */
        void update(box_shapes shape, colours colour, const points_2d hit_box[HIT_BOX_SIZE], const points_2d mid)
        {
            this->shape = shape;
            this->colour = colour;
            middle = mid;
            for (uint8_t row = 0; row < HIT_BOX_SIZE; row++)
            {
                this->hit_box[row] = hit_box[row];
            }
        }

        /**
         * Renders a block thats in a grid with their corresponding properties
         * 
         * @param &grid The reference to the grid the block is in
         * @return void
         */
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

        /**
         * De-renders a block thats in a grid with their corresponding properties
         * 
         * @param &grid The reference to the grid the block is in
         * @return void
         */
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

/**
 * Generates a random series of the blocks
 * 
 * @param &series The reference to the array the that stores the series 
 * @return void
 */
void random_block_series(uint8_t series[NUM_OF_BLOCKS]);

/**
 * Converts the series blocks IDs to the actual blocks entities
 * 
 * @param id The id of the block according to the defined enum (0-6)
 * @return blocks_entity The block that corresponds to the id provided
 */
blocks_entity convert_series_to_block(uint8_t id);

#endif