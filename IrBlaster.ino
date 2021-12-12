#define _DEBUG_

#include "Arduino.h"
#include "SerialDebugContext.h"
#include "ConfigContext.h"
#include "AdafruitIoContext.h"

#include <Dictionary.h>

#include <IRutils.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Dictionary.h>


ConfigContext *configContext;
AdafruitIoContext *adafruitIoContext;

// ----- IR Stuff ----- //
// Because of how this Dictionary was implemented
// it cannot be referenced in a class and we have to
// keep all references the main ino file.
// See: https://github.com/arkhipenko/Dictionary/issues/4
Dictionary &irCodes = *(new Dictionary(20));
const uint16_t IR_LED = 4;
IRsend irSend(IR_LED);

void setup() {
    SerialDebugContext::connectSerialDebugging();

    configContext = new ConfigContext();
    ConfigContext::InitLittleFS();
    configContext->LoadConfig("/config.json");

    irInit();

    adafruitIoContext = new AdafruitIoContext(
        configContext->Config["wifi"]["ssid"],
        configContext->Config["wifi"]["password"],
        configContext->Config["adafruit-io"]["user"],
        configContext->Config["adafruit-io"]["key"],
        configContext->Config["adafruit-io"]["feed"],
        handleMessage
    );
    adafruitIoContext->Connect();
}

void loop() {
    // Wait for messages to come in
    adafruitIoContext->Run();
}

void handleMessage(AdafruitIO_Data *data) {
    char *value = data->value();
    _SP("Message received: ");
    _SPL(value);

    StaticJsonDocument<200> doc;
    DeserializationError err = deserializeJson(doc, value);
    if (err) {
        _SP("JSON deserialization failed with code: ");
        _SPL(err.f_str());
    }
    JsonArray cmds = doc.as<JsonArray>();
    for (JsonObject cmd : cmds) {
        String codeName = cmd["send"];
        blastCode(codeName);
    }
}

// --------- IR BLASTER --------- //
void irInit() {
     _SPL("Init IR blaster");
    JsonArray codes = configContext->Config["ir-codes"];
    for (JsonObject code : codes) {
        String name = code["name"].as<String>();
        String nec = code["code"].as<String>();
        _SP("Adding code '");
        _SP(name);
        _SP("' > '");
        _SP(nec);
        _SP("'...");
        int8_t result = irCodes(name, nec);
        if(result != DICTIONARY_OK) {
            _SPL("FAIL");
            _SP("Dictionary insert returned code: ");
            _SPL(result);
            return;
        }
        _SPL("DONE");
    }
    irSend.begin();
}

void blastCode(String name) {
    _SP("Blasting code '");
    _SP(name);
    _SP("'...");

    String strCode = irCodes[name];

    if(strCode.isEmpty()) {
        _SPL("FAIL");
        _SP("No code found for key: ");
        _SPL(name);
        return;
    }

    uint32_t code = strtol(strCode.c_str(), NULL, 16);
    irSend.sendNEC(code);

    _SPL("DONE");
}
