#include "ButtonContext.h"

ButtonContext::ButtonContext(void (*handler)(int buttonState), int buttonPin) {
    _handler = handler;
    _buttonPin = buttonPin;

    pinMode(_buttonPin, INPUT);
}

void ButtonContext::Run() {
    int reading = digitalRead(_buttonPin);

    if(reading != _lastButtonState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if(reading != _buttonState) {
            _buttonState = reading;

            _handler(_buttonState);
        }
    }

    _lastButtonState = reading;
}