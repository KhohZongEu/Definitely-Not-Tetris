#ifndef GRAPHICS_H
#define GRAPHICS_H
    
#include <SPI.h>
#include <TFT.h>
#include "constants.h"

extern TFT SCREEN;

/**
 * Rotates any point provided so that the screen is in portrait mode and not landscape mode
 * 
 * @param points The point that the object wants to be at on the final render
 * @return points_2d The actual point that is being rendered
 */
points_2d transform(points_2d points);

/**
 * Renders a rectangle
 * 
 * @param points The coordinates of the rectange
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 * @param colour The colour of the rectangle
 * @return void
 */
void render_rect(points_2d points, int width, int height, const colours &colour);

/**
 * Renders a line
 * 
 * @param start The coordinates of the start of the line
 * @param end The coordinates of the end of the line
 * @param colour The colour of the Line
 * @return void
 */
void render_line(points_2d start, points_2d end, const colours &colour);

/**
 * Renders text
 * 
 * @param point The coordinates of the Text
 * @param text A pointer to the text that will be displayed
 * @param colour The colour of the Text
 * @return void
 */
void render_text(points_2d point, const char *text, colours colour);

/**
 * Clears the screen
 * 
 * @param void
 * @return void
 */
void clear_screen();

/**
 * Initilises the graphics
 * 
 * @param void
 * @return void
 */
void graphics_init();

#endif