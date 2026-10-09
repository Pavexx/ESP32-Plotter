#include "Configuracion.h"
#include "ServidorWeb.h"

void ServidorWeb::iniciarAP() {
    Serial.println("\nCreando Access Point...");
    WiFi.mode(WIFI_AP);
    bool result = WiFi.softAP(Config::WIFI_SSID, Config::WIFI_PASSWORD);
    
    if (!result) {
        Serial.println("ERROR creando Access Point");
        return;
    }
    WiFi.softAPConfig(Config::IP, Config::gatewayIP, Config::subnetMask);
    
    Serial.print("-----------------\n  ACCESS POINT\n IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("-----------------");
}

void ServidorWeb::iniciarSV() {
    LittleFS.begin();

    ServidorDNS.setTTL(3600);
    ServidorDNS.start(53, "*", Config::IP);

    // Main page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("GET /");
        //request->send(200, "text/html", "<!DOCTYPE html><html><head><title>Success</title></head><body><p>Hooray</p></body>");
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Android captive portal - generates 204 response code
    server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Android captive portal check detected");
        // Don't redirect here - return 200 to trigger the system to open browser
        request->send(200, "text/plain", "");
    });

    // iPhone captive portal check
    server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("iPhone captive portal check detected");
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Windows captive portal check
    server.on("/ncsi.txt", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Windows captive portal check detected");
        request->send(200, "text/plain", "Microsoft NCSI");
    });

    server.on("/redirect", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Windows redirect check");
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Firefox captive portal check
    server.on("/success.txt", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Firefox captive portal check detected");
        request->send(200, "text/plain", "success");
    });

    // Catch all non-matching requests and serve the page
    server.onNotFound([](AsyncWebServerRequest *request) {
        Serial.print("Unmatched request: ");
        Serial.println(request->url());
        
        // Serve the HTML page for any unmatched request
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.begin();
    Serial.println("Servidor web iniciado");
}

void ServidorWeb::actualizar() {
    ServidorDNS.processNextRequest();
}