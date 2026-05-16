#include "graphics.h"

points_2d transform(points_2d points)
{
    points_2d new_point;
    new_point.x = SCREEN_ROTATION_MATRIX[0].i * points.x + SCREEN_ROTATION_MATRIX[1].i * points.y + 160;
    new_point.y = SCREEN_ROTATION_MATRIX[0].j * points.x + SCREEN_ROTATION_MATRIX[1].j * points.y;

    return new_point;
}

void render_rect(points_2d points, int width, int height, const colours &colour)
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

void move_rect(points_2d &initial, vector_2d direction, const colours &colour, uint8_t cell_size)
{
    if (direction.i != 0 || direction.j != 0)
    {
        render_rect(initial, cell_size, cell_size, COLOUR_BLACK);
    }
    
    if (initial.x + direction.i < SCREEN_WIDTH && initial.x + direction.i >= 0)
    {
        initial.x += direction.i;
    }
    
    if (initial.y + direction.j < SCREEN_HEIGHT && initial.y + direction.j >= 0)
    {
        initial.y += direction.j;
    }
    
    render_rect(initial, cell_size, cell_size, colour);
}

void render_text(points_2d point, char *text, colours colour)
{
    points_2d actual_point = transform(point);
    SCREEN.stroke(colour.b, colour.g, colour.r);

    SCREEN.text(text, actual_point.x, actual_point.y);
    SCREEN.noStroke();
}