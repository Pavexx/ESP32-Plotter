#include "DisplayTFT.h"
#include "Pines.h"

DisplayTFT::DisplayTFT()    //no se por que tiene que ser asi
    : tft(TFT_CS, TFT_DC, TFT_RST) {
}

void DisplayTFT::iniciar() {
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextWrap(false); //texto por defecto (se puede cambiar)
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
}