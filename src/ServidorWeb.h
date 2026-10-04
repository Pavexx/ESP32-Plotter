#pragma once

#include <Arduino.h>

class ServidorWeb {
public:
    void iniciar();
    void actualizar();

private:
    WebServer server{80};
};