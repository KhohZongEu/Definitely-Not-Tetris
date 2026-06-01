#ifndef GRAPHICS_H
#define GRAPHICS_H
    
#include <SPI.h>
#include <TFT.h>
#include "constants.h"

extern TFT SCREEN;

points_2d transform(points_2d points);

void render_rect(points_2d points, int width, int height, const colours &colour);
void render_line(points_2d start, points_2d end, const colours &colour);
void render_text(points_2d point, const char *text, colours colour);

void clear_screen();
void graphics_init();
void render_grid(uint8_t x_offset=0);

#endif