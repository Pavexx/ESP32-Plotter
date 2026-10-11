#include "DisplayTFT.h"
#include "Pines.h"
#include "Imagen.h"

TFT::TFT()    //no se por que tiene que ser asi
    : tft(TFT_CS, TFT_DC, TFT_RST) {
}

void TFT::iniciar() {
    Serial.println("Iniciando TFT...");
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
    //tft.setRotation(1);
    tft.setTextWrap(false); //texto por defecto (se puede cambiar)
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    Serial.println("Display TFT Iniciado");
}
void TFT::dibujarPreview() {
    Serial.println("Dibujando...");
    uint8_t fila, columna;
    for (fila = 0; fila < TFT::alto; fila++) {
            for (columna = 0; columna < TFT::ancho; columna++) {
            tft.drawPixel(columna, fila, img[(fila*TFT::ancho)+columna]);
        }
    }
}
