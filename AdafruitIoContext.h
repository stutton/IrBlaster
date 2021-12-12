#ifndef ADAFRUITIOCONTEXT_H
#define ADAFRUITIOCONTEXT_H

#include "SerialDebugContext.h"
#include "AdafruitIO_WiFi.h"

class AdafruitIoContext {
    public:
        AdafruitIoContext(
            String wifiSsid,
            String wifiPassword,
            String ioUser,
            String ioPassword,
            String feedName,
            void (*handler)(AdafruitIO_Data *data)
        );
        void Connect();
        void Run();

    private:
        String _wifiSsid;
        String _wifiPassword;
        String _ioUser;
        String _ioPassword;
        String _feedName;
        void (*_handler)(AdafruitIO_Data *data);
        AdafruitIO_WiFi *_io;
        AdafruitIO_Feed *_feed;
};

#endif