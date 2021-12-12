#ifndef CONFIGCONTEXT_H
#define CONFIGCONTEXT_H

#include "SerialDebugContext.h"

#include <LittleFS.h>
#include <ArduinoJson.h>

class ConfigContext {
    public:
        StaticJsonDocument<1000> Config;

        static void InitLittleFS();
        ConfigContext() {}
        void LoadConfig(String fileName);
};

#endif