#pragma once

#include <Arduino.h>
#include <SD.h>

class TarjetaSD {
public:
    void iniciar();
    void listarGcodes(Stream& salida);
    bool abrir(const char* direccion);
    void cerrar();
    bool leerSiguienteLinea(char *out, size_t outSize);
    bool escribirLinea(const char* direccion, const char* linea);
    bool crearVacio(const char* direccion);
    void dryRun(const char* direccion);
private:
    File _readFile;
    bool esGcode(const char* nombre);
};