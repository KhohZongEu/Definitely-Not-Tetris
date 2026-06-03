#include "graphics.h"

points_2d transform(points_2d points)
{
    points_2d new_point;
    new_point.x = ROTATION_MATRIX_90[0].i * points.x + ROTATION_MATRIX_90[1].i * points.y + 160;
    new_point.y = ROTATION_MATRIX_90[0].j * points.x + ROTATION_MATRIX_90[1].j * points.y;

    return new_point;
}

void render_rect(points_2d points, uint8_t width, uint8_t height, const colours &colour)
{
    points.y += height; // The + CELL_SIZE is needed at the index is not the same
    points_2d actual_points = transform(points);

    SCREEN.fill(colour.b, colour.g, colour.r);
    SCREEN.rect(actual_points.x, actual_points.y, height, width);
}

void render_line(points_2d start, points_2d end, const colours &colour)
{
    points_2d actual_start = transform(start);
    points_2d actual_end = transform(end);
    
    SCREEN.stroke(colour.b, colour.g, colour.r);
    SCREEN.line(actual_start.x, actual_start.y, actual_end.x, actual_end.y);
    SCREEN.noStroke();
}

void graphics_init()
{
    SCREEN.begin();
    SCREEN.noStroke();
    SCREEN.background(0, 0, 0);
    SCREEN.fill(COLOUR_BLACK.r, COLOUR_BLACK.g, COLOUR_BLACK.b);
}

void render_text(points_2d point, const char *text, colours colour)
{
    points_2d actual_point = transform(point);
    SCREEN.stroke(colour.b, colour.g, colour.r);

    SCREEN.text(text, actual_point.x, actual_point.y);
    SCREEN.noStroke();
}

void clear_screen()
{
    SCREEN.background(0, 0, 0);
}