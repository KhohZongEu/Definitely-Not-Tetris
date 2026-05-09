#ifndef GRAPHICS_H
#define GRAPHICS_H
    
#include <SPI.h>
#include <TFT.h>

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

const colours COLOUR_BLACK = {0, 0, 0};
const colours COLOUR_WHITE = {0xFF, 0xFF, 0xFF};
const colours COLOUR_CYAN = {0x00, 0xFF, 0xFF};
const colours COLOUR_BLUE = {0x00, 0x00, 0xFF};
const colours COLOUR_ORANGE = {0xFF, 0x63, 0x00};
const colours COLOUR_YELLOW = {0xFF, 0xFF, 0x00};
const colours COLOUR_GREEN = {0x00, 0xFF, 0x00};
const colours COLOUR_RED = {0xFF, 0x00, 0x00};
const colours COLOUR_PURPLE = {0x4B, 0x00, 0x82};

extern TFT SCREEN;

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HEIGHT = 160;

/*
Defines a transformation matrix
| 0  -1 |
| 1   0 |
*/
const vector_2d TRANSFORM_MATRIX[2] = {{0, 1}, {-1, 0}};

points_2d transform(points_2d points);

void move_rect(points_2d &initial, vector_2d direction, const colours &colour, uint8_t cell_size);
void render_rect(points_2d points, int width, int height, const colours &colour);
void render_line(points_2d start, points_2d end, const colours &colour);

void graphics_init();
void render_grid(uint8_t x_offset=0);

#endif