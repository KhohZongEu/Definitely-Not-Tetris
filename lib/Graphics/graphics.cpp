#include "graphics.h"

points_2d transform(points_2d points)
{
    points_2d new_point;
    new_point.x = TRANSFORM_MATRIX[0].i * points.x + TRANSFORM_MATRIX[1].i * points.y + 160;
    new_point.y = TRANSFORM_MATRIX[0].j * points.x + TRANSFORM_MATRIX[1].j * points.y;

    return new_point;
}

void render_rect(points_2d points, int width, int height)
{
    points_2d actual_points = transform(points);
    SCREEN.rect(actual_points.x, actual_points.y, width, height);
}

void graphics_init()
{
    SCREEN.begin();
    SCREEN.noStroke();
    SCREEN.background(0, 0, 0);
    SCREEN.fill(255,255,255);
}

void move_object(points_2d &initial, vector_2d direction)
{
    if (direction.i != 0 || direction.j != 0)
    {
        SCREEN.fill(0, 0, 0);
        render_rect(initial, 6, 6);
    }
    
    if (initial.x + direction.i < SCREEN_WIDTH && initial.x + direction.i >= 0)
    {
        initial.x += direction.i;
    }
    
    if (initial.y + direction.j < SCREEN_HEIGHT && initial.y + direction.j >= 0)
    {
        initial.y += direction.j;
    }
    
    SCREEN.fill(255, 255, 255);
    render_rect(initial, 6, 6);
}