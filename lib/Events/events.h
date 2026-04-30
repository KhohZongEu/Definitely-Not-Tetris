#include <Arduino.h>

class events
{
    private:
        uint8_t pin_up;
        uint8_t pin_down;
        uint8_t pin_left;
        uint8_t pin_right;

    public:
        bool up;
        bool down;
        bool left;
        bool right;

        events()
        {
            pin_up = A0;
            pin_down = A1;
            pin_left = A2;
            pin_right = A3;
        }

        events(uint8_t pin_up, uint8_t pin_down, uint8_t pin_left, uint8_t pin_right)
        {
            this->pin_up = pin_up;
            this->pin_down = pin_down;
            this->pin_left = pin_left;
            this->pin_right = pin_right;
        }

        void init()
        {
            pinMode(pin_up, INPUT);
            pinMode(pin_down, INPUT);
            pinMode(pin_left, INPUT);
            pinMode(pin_right, INPUT);
        }

        void update()
        {
            up = digitalRead(pin_up);
            down = digitalRead(pin_down);
            left = digitalRead(pin_left);
            right = digitalRead(pin_right);
        }
};