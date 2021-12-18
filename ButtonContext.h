#ifndef BUTTONCONTEXT_H
#define BUTTONCONTEXT_H

#include "Arduino.h"

class ButtonContext {
    public:
        ButtonContext(void (*handler)(int buttonState), int buttonPin);
        void Run();
    private:
        void (*_handler)(int buttonState);
        int _buttonPin;
        int _buttonState;
        int _lastButtonState;
        unsigned long _lastDebounceTime = 0;
        unsigned long _debounceDelay = 500;
};

#endif