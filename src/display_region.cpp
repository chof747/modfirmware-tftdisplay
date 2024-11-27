#include "display_region.h"
#include <Arduino.h>
#include "tftdisplay.h"

using namespace ModFirmWare;

bool DisplayRegion::hasNewContent()
//****************************************************************************************
{
  return isUpdated();
}

const int DisplayRegion::translateX(const int x) const
//****************************************************************************************
{
  return x + ((x < window.width) ? window.x : window.width);
}

const int DisplayRegion::translateY(const int y) const
//****************************************************************************************
{
  return y + ((y < window.height) ? window.y : window.height);
}

void DisplayRegion::drawImage(imgbuffer_t& buffer, int width, int height)
//****************************************************************************************
{
   for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tft->drawPixel(x, y, buffer[y * width + x]);
        }
    }
}
