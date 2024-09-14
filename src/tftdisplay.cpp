#include "tftdisplay.h"
#include "decodeutf8.h"
#include "gfxlatin1.h"

using namespace ModFirmWare;

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc) : Adafruit_ST7735(cs, dc, rsc),
                                                                       options(INITR_BLACKTAB),
                                                                       orientation(ORIENT_UP_DOWN) {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(ORIENT_RIGHT_LEFT) {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options, uint8_t orientation) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(orientation) {}

bool TFTDisplay::setup(Application* app)
//*****************************************************************************
{
    if (Component::setup(app))
    {
        this->initR(options);
        this->setRotation(orientation);

        return true;
    }
    else
    {
        return false;
    }
}

void TFTDisplay::loop()
//*****************************************************************************
{

}

size_t TFTDisplay::printlnStr(const char str[])
//*****************************************************************************
{
    return this->println(utf8tocp(String(str)));
}

size_t TFTDisplay::printStr(const char str[])
//*****************************************************************************
{
    return this->print(utf8tocp(String(str)));
}