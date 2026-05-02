#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <TFT.h>
#include <Arduino.h>

struct points_2d
{
    int x;
    int y;
};

struct vector_2d
{
    int i;
    int j;
};

extern TFT SCREEN;

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 160;

/*
Defines a transformation matrix
| 0  -1 |
| 1   0 |
*/
const vector_2d TRANSFORM_MATRIX[2] = {{0, 1}, {-1, 0}};


points_2d transform(points_2d points);
void render_rect(points_2d points, int width, int height);

void graphics_init();

void move_object(points_2d &initial, vector_2d direction);


#endif