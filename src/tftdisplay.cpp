#include "tftdisplay.h"
#include "decodeutf8.h"
#include "gfxlatin1.h"

using namespace ModFirmWare;

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc) : Adafruit_ST7735(cs, dc, rsc),
                                                                       options(INITR_BLACKTAB),
                                                                       orientation(ORIENT_LEFT_RIGHT),regions() {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(ORIENT_RIGHT_LEFT), regions() {}
TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options, uint8_t orientation) : Adafruit_ST7735(cs, dc, rsc),
                                                                                        options(options),
                                                                                        orientation(orientation), regions() {}

bool TFTDisplay::setup(Application* app)
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
    for(std::list<DisplayRegion*>::iterator it = regions.begin();it != regions.end();++it)
    {
        DisplayRegion* dr = *it;
        if (dr->hasNewContent())
        {
            dr->update();
        }
    }

}

size_t TFTDisplay::registerRegion(DisplayRegion* region)
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
  std::list<DisplayRegion*>::iterator it = regions.begin();

  while(regions.end() != it)
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