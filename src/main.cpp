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
    Serial.begin(115200);
    static game_entity game(GRID_OFFSET_X, GRID_OFFSET_Y);
    
    game.init_render();
    
    while (true)
    {
      while (game.start == true)
      {
        game.main_game();
      }
      
      if (game.start == false)
      {
        game.event.update();

        if (game.event.button_pressed == UP)
        {
          game.start = true;
        }
        else if (game.event.button_pressed == DOWN)
        {
          game.reset();
        }

      }

    }
}

void loop()
{
  
}

