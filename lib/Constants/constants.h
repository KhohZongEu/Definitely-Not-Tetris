#ifndef CONSTANT_H
#define CONSTANT_H

#include <Arduino.h>

struct points_2d
{
    uint8_t x;
    uint8_t y;
};

struct vector_2d
{
    int8_t i;
    int8_t j;
};

struct colours
{
    uint8_t r;
    uint8_t g; 
    uint8_t b;
};

const uint8_t MAX_CELLS_X = 10;
const uint8_t MAX_CELLS_Y = 20;
const uint8_t CELL_SIZE = 6;
const uint8_t LINE_WIDTH = 1;

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 160;

const colours COLOUR_BLACK = {0, 0, 0};
const colours COLOUR_WHITE = {0xFF, 0xFF, 0xFF};
const colours COLOUR_CYAN = {0x00, 0xFF, 0xFF};
const colours COLOUR_BLUE = {0x00, 0x00, 0xFF};
const colours COLOUR_ORANGE = {0xFF, 0x63, 0x00};
const colours COLOUR_YELLOW = {0xFF, 0xFF, 0x00};
const colours COLOUR_GREEN = {0x00, 0xFF, 0x00};
const colours COLOUR_RED = {0xFF, 0x00, 0x00};
const colours COLOUR_PURPLE = {0x4B, 0x00, 0x82};

const uint8_t HIT_BOX_SIZE = 4;

const uint8_t NUM_OF_BLOCKS = 7;

/*
Defines a transformation matrix
| 0  -1 |
| 1   0 |
*/
const vector_2d ROTATION_MATRIX_90[2] = {{0, 1}, {-1, 0}};

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
#endif