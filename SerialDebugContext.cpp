#include "SerialDebugContext.h"

void SerialDebugContext::connectSerialDebugging() {
#ifdef _DEBUG_
    Serial.begin(115200);
    delay(500);
    while(!Serial) continue;
    delay(500);
    _SPL("");
    _SPL("---------------------------");
    _SPL("Serial debugging connected.");
    _SPL("---------------------------");
#endif
}