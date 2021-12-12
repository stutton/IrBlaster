#ifndef SERIALDEBUGCONTEXT_H
#define SERIALDEBUGCONTEXT_H

#include "Arduino.h"

#ifndef _DEBUG_
#define _DEBUG_
#endif

#ifdef _DEBUG_
#define _SP(s) Serial.print(s);
#define _SPL(s) Serial.println(s);
#else
#define _SP(s)
#define _SPL(s)
#endif

class SerialDebugContext {
    public:
        static void connectSerialDebugging();
    private:
        SerialDebugContext() {}
};

#endif