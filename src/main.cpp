#include <Arduino.h>

#include "game.h"

const uint8_t CS =  10;
const uint8_t DC =  9;
const uint8_t RST = 8;

const uint8_t GRID_OFFSET_X = 9;
const uint8_t GRID_OFFSET_Y = 10;
TFT SCREEN = TFT(CS, DC, RST);

void setup()
{
    game_entity game(GRID_OFFSET_X, GRID_OFFSET_Y);

    game.init_render();

    while (true)
    {
      game.main_game();
    }
}

void loop()
{
  
}

