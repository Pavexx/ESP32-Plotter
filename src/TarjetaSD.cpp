#include "TarjetaSD.h"
#include "Pines.h"

void TarjetaSD::iniciar() {
    Serial.println("Iniciando SD...");

    bool ok = SD.begin(SD_CS);
    if (!ok) {
        Serial.println("ERROR iniciando SD");
        return;
    }
    Serial.println("SD iniciada correctamente");
}

void TarjetaSD::listarGcodes(Stream& salida) {
    File raiz = SD.open("/");               //abre el directorio raiz
    File item;                              //archivo a analizar
    while ((item = raiz.openNextFile())) {
        if (!item.isDirectory() && esGcode(item.name())) {
            salida.println(item.name());   
            //envia el nombre por stream, se puede usar con Serial o GFX
        }
        item.close();
    }
    raiz.close();
}

bool TarjetaSD::abrir(const char* direccion) {
    cerrar();
    _readFile = SD.open(direccion, FILE_READ);
    return (bool)_readFile;
}

void TarjetaSD::cerrar() {
    if (_readFile) _readFile.close();
}

bool leerLinea(File &file, uint32_t linea, char *out, size_t outSize) {
    file.seek(0);

    uint32_t currentLine = 0;
    size_t i = 0;
    bool inTarget = false;

    while (file.available()) {
        char c = file.read();
        if (c == '\r') continue;
        if (c == '\n') {
            if (inTarget) {
                out[i] = '\0';
                return true;
            }
            currentLine++;
            continue;
        }
        if (currentLine == linea) {
            inTarget = true;
            if (i < outSize - 1) out[i++] = c;
        }
    }
    if (inTarget) {
        out[i] = '\0';
        return true;
    }
    return false;
}

bool esGcode(const char* nombre) {
    const char* extension = strrchr(nombre, '.');
    if (!extension) {
        return false;
    }
    return strcasecmp(extension, ".gcode") == 0;
}
