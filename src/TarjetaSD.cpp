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

bool esGcode(const char* nombre) {
    const char* extension = strrchr(nombre, '.');
    if (!extension) {
        return false;
    }
    return strcasecmp(extension, ".gcode") == 0;
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
