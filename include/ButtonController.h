#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <Arduino.h>

#ifndef MAX_BUTTON_COUNT
    #define MAX_BUTTON_COUNT 6
    #pragma message "Assuming default number of buttons:  " MAX_BUTTON_COUNT
#else
    #pragma message "Override default number of buttons. New count:  " MAX_BUTTON_COUNT
#endif

typedef void (*ButtonCallback)(const uint8_t index, bool value);

typedef struct {
    unsigned long lastDebounce;
    uint8_t tempState;
    bool state;
    uint8_t pin;
} Button;

class ButtonController {

    private:

        Button _buttons[MAX_BUTTON_COUNT];
        uint8_t _buttonCount = 0;
        unsigned long  _debounceTime = 50;
        ButtonCallback _buttonCallback = 0;

    public:

        ButtonController();

        void link(uint8_t pin);
        void update(uint8_t index);
        void poll();

        void setDebounceTime(long debounce);
        void setButtonCallback(ButtonCallback cb);
};

#endif // __BUTTONS_H__