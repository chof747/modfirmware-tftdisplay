#include "tftdisplay.h"
#include "decodeutf8.h"
#include "gfxlatin1.h"

using namespace ModFirmWare;

#ifndef BLINK_FREQUENCY 
#define BLINK_FREQUENCY 1000
#endif

#define LOGTAG "tft"

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc)
    : Adafruit_ST7735(cs, dc, rsc),
      options(INITR_BLACKTAB),
      orientation(ORIENT_LEFT_RIGHT), regions(),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY) {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options)
    : Adafruit_ST7735(cs, dc, rsc),
      options(options),
      orientation(ORIENT_RIGHT_LEFT), regions(),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY) {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options, uint8_t orientation)
    : Adafruit_ST7735(cs, dc, rsc),
      options(options),
      orientation(orientation), regions(),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY) {}

bool TFTDisplay::setup(Application *app)
//*****************************************************************************
{
    if (Component::setup(app))
    {
        this->initR(options);
        this->setRotation(orientation);

        fillScreen(ST7735_BLACK);

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
    static time_t lastBlink = 0;
    bool blinkChange = false;

    if (BLINK_FREQUENCY <= (millis() - lastBlink))
    {
        blinkstate = !blinkstate;
        lastBlink = millis();
        blinkChange = true;
    }

    for (std::list<DisplayRegion *>::iterator it = regions.begin(); it != regions.end(); ++it)
    {
        DisplayRegion *dr = *it;
        if ((dr->hasNewContent()) || ((dr->isBlinking()) && (blinkChange)))
        {
            dr->update(blinkstate);
        }
    }
}

size_t TFTDisplay::registerRegion(DisplayRegion *region)
//*****************************************************************************
{
    if (region)
    {
        regions.push_back(region);
        return regions.size();
    }

    return 0;
}

bool TFTDisplay::unregisterRegion(DisplayRegion *region)
//*****************************************************************************
{
    std::list<DisplayRegion *>::iterator it = regions.begin();

    while (regions.end() != it)
    {
        if (*it == region)
        {
            it = regions.erase(it);
            return true;
        }
        else
        {
            ++it;
        }
    }

    return false;
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