#pragma once

#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>

class ServidorWeb {
public:
    void iniciar();
    void actualizar();
    IPAddress IP() const;
private:
    WebServer server{80};
};