#include "IndicatorContext.h"

IndicatorContext::IndicatorContext(uint16_t readyLed, uint16_t connectingLed) {
    _readyLed = readyLed;
    _connectingLed = connectingLed;

    pinMode(_readyLed, OUTPUT);
    pinMode(_connectingLed, OUTPUT);
    digitalWrite(_connectingLed, LOW);
    digitalWrite(_readyLed, LOW);
}

void IndicatorContext::SetStatus(Status status) {
    if(status == Connecting) {
        digitalWrite(_connectingLed, HIGH);
        digitalWrite(_readyLed, LOW);
    }
    else if (status == Ready) {
        digitalWrite(_connectingLed, LOW);
        digitalWrite(_readyLed, HIGH);
    }
    else if (status == IrPrograming) {
        digitalWrite(_connectingLed, HIGH);
        digitalWrite(_readyLed, HIGH);
    }
}