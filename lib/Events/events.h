#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>

enum button_type
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class events
{
    private:
        uint8_t pin_up;
        uint8_t pin_down;
        uint8_t pin_left;
        uint8_t pin_right;
        
    public:
        button_type button_pressed;

        /**
         * Default Constructor for the Events class
         * 
         * @param void 
         * @return void
         */
        events()
        {
            pin_up = A0;
            pin_down = A1;
            pin_left = A2;
            pin_right = A3;
        }

        /**
         * Constructor for the Events class with user provided arguements
         * 
         * @param pin_up The pin for the top button
         * @param pin_down The pin for the bottom button
         * @param pin_left The pin for the left button
         * @param pin_right The pin for the right button
         * @return void
         */
        events(uint8_t pin_up, uint8_t pin_down, uint8_t pin_left, uint8_t pin_right)
        {
            this->pin_up = pin_up;
            this->pin_down = pin_down;
            this->pin_left = pin_left;
            this->pin_right = pin_right;
        }
        
        /**
         * Initialises the pins for usage
         * 
         * @param void 
         * @return void
         */
        void init()
        {
            pinMode(pin_up, INPUT);
            pinMode(pin_down, INPUT);
            pinMode(pin_left, INPUT);
            pinMode(pin_right, INPUT);
        }

        /**
         * Updates the state of which button is pressed
         * 
         * @param void 
         * @return void
         */
        void update()
        {
            if (digitalRead(pin_up))
            {
                button_pressed = UP;
            }
            else if (digitalRead(pin_down))
            {
                button_pressed = DOWN;
            }
            else if (digitalRead(pin_left))
            {
                button_pressed = LEFT;
            }
            else if (digitalRead(pin_right))
            {
                button_pressed = RIGHT;
            }
            else
            {
                button_pressed = NONE;
            }
        }
};

#endif