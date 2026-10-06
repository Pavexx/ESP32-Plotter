#include "Configuracion.h"
#include "ServidorWeb.h"

void ServidorWeb::iniciar() {
    Serial.println("\nCreando Access Point...");
    WiFi.mode(WIFI_AP);
    bool result = WiFi.softAP(Configuracion::WIFI_SSID, Configuracion::WIFI_PASSWORD);
    
    if (!result) {
        Serial.println("ERROR creando Access Point");
        return;
    }
    Serial.println("\n ACCESS POINT \nIP: ");
    Serial.print(WiFi.softAPIP());
}

IPAddress ServidorWeb::IP() const {
    return WiFi.softAPIP();
}