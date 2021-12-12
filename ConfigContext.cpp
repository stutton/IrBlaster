#include "ConfigContext.h"

void ConfigContext::InitLittleFS() {
    LittleFSConfig cfg;
    cfg.setAutoFormat(false);
    LittleFS.setConfig(cfg);

    _SP("Mounting FS...");
    if(LittleFS.begin()){
        _SPL("DONE");
    }
    else{
        _SPL("FAIL");
    }
}

void ConfigContext::LoadConfig(String fileName) {
    _SP("Load settings...");
    File f = LittleFS.open("/config.json", "r");
    if (!f) {
        _SPL("FAIL");
        _SPL("Failed to open settings file");
        return;
    }

    DeserializationError err = deserializeJson(Config, f);
    f.close();
    if (err) {
        _SPL("FAIL");
        _SP("JSON deserialization failed with code: ");
        _SPL(err.f_str());
        return;
    }
    _SPL("DONE")
}
