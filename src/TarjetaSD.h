#pragma once

#include <Arduino.h>
#include <SD.h>

class TarjetaSD {
public:
    void iniciar();
    void listarGcodes(Stream& salida);
    bool escribirLinea(const char* direccion, const char* linea);
    bool crearVacio(const char* direccion);
    bool abrir(const char* direccion);
    bool leerLinea(char* buffer, size_t bufferSize);
    void cerrar();
private:
    File _readFile;;
    bool esGcode(const char* nombre);
};