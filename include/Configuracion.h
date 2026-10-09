#pragma once
#include <WiFi.h>

namespace Configuracion {
    constexpr char WIFI_SSID[] = "Plotter-AP";
    constexpr char WIFI_PASSWORD[] = "";
    const IPAddress IPLocal(4, 3, 2, 1);  // ESP32 IP address
    const IPAddress gatewayIP(4, 3, 2, 1);
    const IPAddress subnetMask(255, 255, 255, 0);
    const char* DominioLocal = "esp32.local";
}