#pragma once

#include <WiFi.h>
#include <Arduino.h>
//#include <WebServer.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "DNSServer.h"


class ServidorWeb {
public:
    void iniciar();
    void actualizar();
    IPAddress IP() const;
private:
    AsyncWebServer server{80};
    DNSServer ServidorDNS;
};