#include "TarjetaSD.h"
#include "GCodes.h"
#include "Pines.h"

GCodes gcodes;

void TarjetaSD::iniciar() {
    Serial.println("Iniciando SD...");
    //SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    bool ok = SD.begin(SD_CS, SPI, 4000000);
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

bool TarjetaSD::leerSiguienteLinea(char *out, size_t outSize) {
    if (out == nullptr || outSize == 0) return false;
    out[0] = '\0';

    if (!_readFile.available()) return false;   // no more data

    size_t i = 0;
    while (_readFile.available()) {
        int c = _readFile.read();
        if (c < 0) break;                  // read error or EOF
        if (c == '\r') continue;           // ignore CR in CRLF files
        if (c == '\n') break;              // end of line
        if (i < outSize - 1) out[i++] = (char)c;
    }
    out[i] = '\0';
    return true;
}

bool TarjetaSD::esGcode(const char* nombre) {
    const char* extension = strrchr(nombre, '.');
    if (!extension) {
        return false;
    }
    return strcasecmp(extension, ".gcode") == 0;
}

void TarjetaSD::dryRun(const char* direccion) {
    if (!abrir(direccion)) {
        return;
    }

    Serial.println("iniciando dry run");

    char linea[128];
    uint32_t numero = 0;

    while (leerSiguienteLinea(linea, sizeof(linea)) && numero < 100) {
        Serial.print(numero++);
        Serial.print(": ");
        Serial.println(linea);
    }

    Serial.println("finalizado");
    cerrar();
}