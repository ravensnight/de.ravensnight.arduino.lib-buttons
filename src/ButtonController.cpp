#include <ButtonController.h>

ButtonController::ButtonController() {
    _buttonCallback = 0;
    _buttonCount = 0;
}

void ButtonController::setButtonCallback(ButtonCallback cb) {
    _buttonCallback = cb;    
}

void ButtonController::link(uint8_t pin) {
    if (_buttonCount < MAX_BUTTON_COUNT) {
        _buttons[_buttonCount].pin = pin;
        _buttons[_buttonCount].state = (digitalRead(pin) == 0);   

        pinMode(pin, INPUT_PULLUP);
        _buttonCount++;
    }

}

void ButtonController::update(uint8_t index) {
    if (index >= _buttonCount) return;

    Button& b = _buttons[index];
    bool newstate = (digitalRead(b.pin) == 0);    

    if (newstate != b.tempState) {
        b.lastDebounce = millis();
    }

    if ((millis() - b.lastDebounce) > _debounceTime) {
        if (newstate != b.state) {
            b.state = newstate;
            if (_buttonCallback != 0) {
                _buttonCallback(index, b.state);
            }
        }        
    }

    b.tempState = newstate;
}

void ButtonController::poll() {
    for (uint8_t i = 0; i < _buttonCount; i++) {
        update(i);
    }
}

void ButtonController::setDebounceTime(long time) {
    this->_debounceTime = time;
}
