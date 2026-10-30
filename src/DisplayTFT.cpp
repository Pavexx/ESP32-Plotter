#include "DisplayTFT.h"
#include "Pines.h"
#include "Imagen.h"
#include "Fonts/FreeSansBold9pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"

DisplayTFT::DisplayTFT()
    : tft(TFT_CS, TFT_DC, TFT_RST) {
}

void DisplayTFT::iniciar() {
    Serial.println("Iniciando TFT...");
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
    //tft.setRotation(1);
    tft.setTextWrap(false); //texto por defecto (se puede cambiar)
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    Serial.println("Display TFT Iniciado");
}
void DisplayTFT::dibujarPreview() {
    Serial.println("Dibujando...");
    uint8_t fila, columna;
    for (fila = 0; fila < alto; fila++) {
            for (columna = 0; columna < ancho; columna++) {
            tft.drawPixel(columna, fila, img[(fila*ancho)+columna]);
        }
    }
}
void DisplayTFT::dibujarUI(int8_t estado, int8_t i) {
    switch (estado) {
    case 1:
        tft.fillScreen(0xFFFF);
        tft.setFont(&FreeSansBold12pt7b);
        tft.setTextColor(0x0014);
        tft.setCursor(26, 26);
        tft.print("Plotter");
        boton(i==1, i);
        boton(i==2, i);
        boton(i==3, i);
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    default:
        break;
    }
}
void DisplayTFT::boton(bool selecc, uint8_t i) {
    tft.fillRoundRect(7, 37+i*41, 116, 36, 7, 0x0014);
    if (selecc) {
        tft.fillRoundRect(5, 35+i*41, 120, 40, 7, 0xFC00);
    }
    tft.setFont(&FreeSansBold9pt7b);
    tft.setTextColor(selecc ? 0xFC00 : 0xFFFF);
    switch (i) {
    case 0:
        tft.setCursor(33, 60);
        tft.print("Dibujar");
        break;
    case 1:
        tft.setCursor(33, 101);
        tft.print("Manual");
        break;
    default:
        tft.setCursor(12, 142);
        tft.print("Prueba Hoja");
        break;
    }
}