#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <Arduino.h>

typedef void (*ButtonCallback)(const uint8_t index, bool value);

typedef struct {
    unsigned long lastDebounce;
    uint8_t tempState;
    bool state;
    uint8_t pin;
} Button;

class ButtonController {

    private:

        Button* _buttons = 0;
        uint8_t _maxButtons = 0;
        uint8_t _buttonCount = 0;
        unsigned long  _debounceTime = 50;
        ButtonCallback _buttonCallback = 0;

    public:

        ButtonController(uint8_t maxButtons);

        void link(uint8_t pin);
        void update(uint8_t index);
        void poll();

        void setDebounceTime(long debounce);
        void setButtonCallback(ButtonCallback cb);
};

#endif // __BUTTONS_H__