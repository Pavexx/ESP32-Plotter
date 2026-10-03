#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

#include <TFT_eSPI.h>
#include <lvgl.h>

// ============================================================
// CONFIGURACIÓN
// ============================================================

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  160

#define IMAGE_SIZE \
    (SCREEN_WIDTH * SCREEN_HEIGHT * 2)


// ============================================================
// WIFI ACCESS POINT
// ============================================================

const char *AP_SSID = "ESP32-LVGL";
const char *AP_PASSWORD = "12345678";


// ============================================================
// OBJETOS
// ============================================================

TFT_eSPI tft = TFT_eSPI();

WebServer server(80);


// ============================================================
// LVGL
// ============================================================

// Buffer de dibujo de LVGL.
//
// 128 x 20 x 2 bytes = 5120 bytes

static uint16_t lvgl_buffer[
    SCREEN_WIDTH * 20
];

static lv_display_t *display;


// ============================================================
// BUFFER PARA LA IMAGEN RECIBIDA
// ============================================================

// 128 * 160 * 2 = 40960 bytes
//
// Esta memoria se reserva en heap.
//
// No se utiliza para LVGL.
// Solamente contiene la imagen RGB565
// recibida desde el navegador.

uint8_t *imageBuffer = nullptr;


// ============================================================
// ESTADO
// ============================================================

bool imageReceived = false;

size_t receivedBytes = 0;


// ============================================================
// LVGL -> TFT
// ============================================================

void my_disp_flush(
    lv_display_t *disp,
    const lv_area_t *area,
    uint8_t *px_map
)
{
    uint32_t width =
        area->x2 - area->x1 + 1;

    uint32_t height =
        area->y2 - area->y1 + 1;


    tft.startWrite();

    tft.setAddrWindow(
        area->x1,
        area->y1,
        width,
        height
    );

    tft.pushColors(
        (uint16_t *)px_map,
        width * height,
        true
    );

    tft.endWrite();


    lv_display_flush_ready(disp);
}


// ============================================================
// MOSTRAR IMAGEN RGB565
// ============================================================

void mostrarImagen()
{
    if (!imageBuffer)
    {
        return;
    }

    Serial.println(
        "Mostrando imagen..."
    );


    tft.startWrite();

    tft.setAddrWindow(
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );


    // --------------------------------------------------------
    // La imagen llega desde JavaScript como:
    //
    // LOW BYTE
    // HIGH BYTE
    //
    // RGB565 little endian.
    //
    // TFT_eSPI necesita el intercambio correspondiente.
    // --------------------------------------------------------

    tft.pushColors(
        (uint16_t *)imageBuffer,
        SCREEN_WIDTH * SCREEN_HEIGHT,
        true
    );


    tft.endWrite();


    Serial.println(
        "Imagen mostrada."
    );
}


// ============================================================
// RECIBIR IMAGEN POR HTTP
// ============================================================

void handleImageUpload()
{
    HTTPUpload &upload =
        server.upload();


    // --------------------------------------------------------
    // INICIO
    // --------------------------------------------------------

    if (upload.status == UPLOAD_FILE_START)
    {
        Serial.println();
        Serial.println(
            "================================"
        );

        Serial.println(
            "Comenzando transferencia"
        );

        Serial.print(
            "Archivo: "
        );

        Serial.println(
            upload.filename
        );


        receivedBytes = 0;
        imageReceived = false;


        // ----------------------------------------------------
        // Reservar buffer
        // ----------------------------------------------------

        if (imageBuffer)
        {
            free(imageBuffer);

            imageBuffer = nullptr;
        }


        imageBuffer =
            (uint8_t *)malloc(
                IMAGE_SIZE
            );


        if (!imageBuffer)
        {
            Serial.println(
                "ERROR: No hay memoria"
            );

            return;
        }


        Serial.print(
            "Buffer reservado: "
        );

        Serial.print(
            IMAGE_SIZE
        );

        Serial.println(
            " bytes"
        );
    }


    // --------------------------------------------------------
    // DATOS
    // --------------------------------------------------------

    else if (
        upload.status ==
        UPLOAD_FILE_WRITE
    )
    {
        if (!imageBuffer)
        {
            return;
        }


        size_t bytes =
            upload.currentSize;


        // ----------------------------------------------------
        // Evitar overflow
        // ----------------------------------------------------

        if (
            receivedBytes + bytes >
            IMAGE_SIZE
        )
        {
            Serial.println(
                "ERROR: Imagen demasiado grande"
            );

            return;
        }


        memcpy(
            imageBuffer + receivedBytes,
            upload.buf,
            bytes
        );


        receivedBytes += bytes;


        Serial.print(
            "\rRecibidos: "
        );

        Serial.print(
            receivedBytes
        );

        Serial.print(
            " / "
        );

        Serial.print(
            IMAGE_SIZE
        );

        Serial.print(
            " bytes"
        );
    }


    // --------------------------------------------------------
    // FIN
    // --------------------------------------------------------

    else if (
        upload.status ==
        UPLOAD_FILE_END
    )
    {
        Serial.println();
        Serial.println(
            "Transferencia terminada."
        );


        Serial.print(
            "Bytes recibidos: "
        );

        Serial.println(
            receivedBytes
        );


        // ----------------------------------------------------
        // Verificar tamaño
        // ----------------------------------------------------

        if (
            receivedBytes ==
            IMAGE_SIZE
        )
        {
            imageReceived = true;

            mostrarImagen();

            Serial.println(
                "Imagen RGB565 válida."
            );
        }
        else
        {
            Serial.println(
                "ERROR: Tamaño incorrecto."
            );

            Serial.print(
                "Esperado: "
            );

            Serial.println(
                IMAGE_SIZE
            );

            Serial.print(
                "Recibido: "
            );

            Serial.println(
                receivedBytes
            );
        }


        Serial.println(
            "================================"
        );
    }
}


// ============================================================
// INDEX.HTML
// ============================================================

void handleRoot()
{
    File file =
        LittleFS.open(
            "/data/index.html",
            "r"
        );


    if (!file)
    {
        server.send(
            500,
            "text/plain",
            "No se encuentra index.html"
        );

        return;
    }


    server.streamFile(
        file,
        "text/html"
    );


    file.close();
}


// ============================================================
// ESTADO DEL ESP32
// ============================================================

void handleStatus()
{
    String json = "{";

    json +=
        "\"imageReceived\":";

    json +=
        imageReceived
        ? "true"
        : "false";

    json += ",";

    json +=
        "\"receivedBytes\":";

    json +=
        String(receivedBytes);

    json += ",";

    json +=
        "\"expectedBytes\":";

    json +=
        String(IMAGE_SIZE);

    json += ",";

    json +=
        "\"freeHeap\":";

    json +=
        String(ESP.getFreeHeap());

    json += "}";


    server.send(
        200,
        "application/json",
        json
    );
}


// ============================================================
// 404
// ============================================================

void handleNotFound()
{
    server.send(
        404,
        "text/plain",
        "404 - No encontrado"
    );
}


// ============================================================
// WIFI
// ============================================================

void setupWiFi()
{
    Serial.println();

    Serial.println(
        "Creando Access Point..."
    );


    WiFi.mode(
        WIFI_AP
    );


    bool result =
        WiFi.softAP(
            AP_SSID,
            AP_PASSWORD
        );


    if (!result)
    {
        Serial.println(
            "ERROR creando Access Point"
        );

        return;
    }


    IPAddress ip =
        WiFi.softAPIP();


    Serial.println();
    Serial.println(
        "================================"
    );

    Serial.println(
        " ACCESS POINT"
    );

    Serial.println(
        "================================"
    );

    Serial.print(
        "SSID: "
    );

    Serial.println(
        AP_SSID
    );

    Serial.print(
        "Password: "
    );

    Serial.println(
        AP_PASSWORD
    );

    Serial.print(
        "IP: "
    );

    Serial.println(
        ip
    );

    Serial.println(
        "================================"
    );
}


// ============================================================
// WEB SERVER
// ============================================================

void setupWebServer()
{
    // Página principal
    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );


    // Estado
    server.on(
        "/status",
        HTTP_GET,
        handleStatus
    );


    // Upload de imagen
    server.on(
        "/upload",
        HTTP_POST,

        []()
        {
            server.send(
                200,
                "text/plain",
                "OK"
            );
        },

        handleImageUpload
    );


    server.onNotFound(
        handleNotFound
    );


    server.begin();


    Serial.println(
        "Servidor HTTP iniciado."
    );
}


// ============================================================
// LVGL
// ============================================================

void setupLVGL()
{
    Serial.println(
        "Inicializando LVGL..."
    );


    lv_init();


    display =
        lv_display_create(
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        );


    lv_display_set_buffers(
        display,
        lvgl_buffer,
        nullptr,
        sizeof(lvgl_buffer),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );


    lv_display_set_flush_cb(
        display,
        my_disp_flush
    );


    // --------------------------------------------------------
    // Pantalla inicial
    // --------------------------------------------------------

    lv_obj_t *label =
        lv_label_create(
            lv_screen_active()
        );


    lv_label_set_text(
        label,
        "ESP32\n"
        "ST7735\n"
        "LVGL\n\n"
        "Conectate a:\n"
        "ESP32-LVGL"
    );


    lv_obj_center(
        label
    );


    Serial.println(
        "LVGL iniciado."
    );
}


// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(
        115200
    );


    delay(500);


    Serial.println();
    Serial.println();

    Serial.println(
        "================================"
    );

    Serial.println(
        " ESP32 IMAGE SERVER"
    );

    Serial.println(
        " ST7735 + LVGL"
    );

    Serial.println(
        "================================"
    );


    // --------------------------------------------------------
    // LittleFS
    // --------------------------------------------------------

    if (!LittleFS.begin(true))
    {
        Serial.println(
            "ERROR: LittleFS"
        );

        return;
    }


    Serial.println(
        "LittleFS OK"
    );


    // --------------------------------------------------------
    // TFT
    // --------------------------------------------------------

    tft.init();

    tft.setRotation(
        0
    );

    tft.fillScreen(
        TFT_BLACK
    );


    Serial.println(
        "TFT OK"
    );


    // --------------------------------------------------------
    // LVGL
    // --------------------------------------------------------

    setupLVGL();


    // --------------------------------------------------------
    // WiFi
    // --------------------------------------------------------

    setupWiFi();


    // --------------------------------------------------------
    // Web
    // --------------------------------------------------------

    setupWebServer();


    Serial.println();
    Serial.println(
        "Sistema listo."
    );
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
    // Servidor web
    server.handleClient();


    // LVGL
    lv_timer_handler();


    delay(5);
}