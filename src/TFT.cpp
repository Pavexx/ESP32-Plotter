#include "TFT.h"
#include "Pines.h"

TFT::TFT()
    : tft(TFT_CS, TFT_DC, TFT_RST) {
}

void TFT::iniciar() {
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextWrap(false);
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
}