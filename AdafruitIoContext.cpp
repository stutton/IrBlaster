#include "AdafruitIoContext.h"

AdafruitIoContext::AdafruitIoContext(
    String wifiSsid,
    String wifiPassword,
    String ioUser,
    String ioPassword,
    String feedName,
    void (*handler)(AdafruitIO_Data *data)
) {
    _wifiSsid = wifiSsid;
    _wifiPassword = wifiPassword;
    _ioUser = ioUser;
    _ioPassword = ioPassword;
    _feedName = feedName;
    _handler = handler;
}

void AdafruitIoContext::Connect() {
    _SP("Wifi: ");
    _SPL(_wifiSsid);
    _SP("Adafruit User: ");
    _SPL(_ioUser);
    _SP("Feed: ")
    _SPL(_feedName);
    _SP("Connecting to Adafruit IO");

    _io = new AdafruitIO_WiFi(
        _ioUser.c_str(),
        _ioPassword.c_str(),
        _wifiSsid.c_str(),
        _wifiPassword.c_str()
    );

    _io->connect();
    _feed = _io->feed(_feedName.c_str());
    _feed->onMessage(_handler);

    int i = 0;
    while(_io->mqttStatus() < AIO_CONNECTED) {
        if(i % 4 == 0) {
            _SP(".");
            i = 0;
        }
        delay(500);
        i++;
    }

    _SPL("CONNECTED");
    _SPL(_io->statusText());
}

void AdafruitIoContext::Run() {
    _io->run();
}