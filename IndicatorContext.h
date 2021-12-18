#ifndef INDICATORCONTEXT_H
#define INDICATORCONTEXT_H

#include "Arduino.h"

enum Status {
    Connecting,
    Ready,
    IrPrograming
};

class IndicatorContext {
    public:
        IndicatorContext(uint16_t readyLed, uint16_t connectingLed);
        void SetStatus(Status status);

    private:
        uint16_t _readyLed;
        uint16_t _connectingLed;
};

#endif // !INDICATORCONTEXT_H