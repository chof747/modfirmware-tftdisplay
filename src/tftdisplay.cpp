#include "tftdisplay.h"
#include "decodeutf8.h"
#include "gfxlatin1.h"

TFTDisplay::TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc) : Adafruit_ST7735(cs, dc, rsc),
                                                                       options(INITR_BLACKTAB),
                                                                       orientation(ORIENT_UP_DOWN) {}
TFTDisplay::TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc, uint8_t options) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(ORIENT_RIGHT_LEFT) {}
TFTDisplay::TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc, uint8_t options, uint8_t orientation) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(orientation) {}

bool TFTDisplay::setup()
{
    this->initR(options);
    this->setRotation(orientation);

    return true;
}

void TFTDisplay::loop()
{

}

size_t TFTDisplay::printlnStr(const char str[])
{
    return this->println(utf8tocp(String(str)));
}

size_t TFTDisplay::printStr(const char str[])
{
    return this->print(utf8tocp(String(str)));
}