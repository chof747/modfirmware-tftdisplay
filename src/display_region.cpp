#include "display_region.h"
#include <Arduino.h>
#include "tftdisplay.h"

using namespace ModFirmWare;

#define LOGTAG "display_reg"

void DisplayRegion::update(bool blink)
//****************************************************************************************
{
  if (isUpdated())
  {
    updateCanvas();
  }

  doBlinking(blink);
  //logger->debug(LOGTAG, "x = %d, y = %d, w = %d, h = %d", window.x, window.y, canvas.width(), canvas.height());
  tft->drawRGBBitmap(window.x,window.y, canvas.getBuffer(), canvas.width(), canvas.height());
}

bool DisplayRegion::hasNewContent()
//****************************************************************************************
{
  return isUpdated();
}

const unsigned int DisplayRegion::getTextHeight(const char* text)
//****************************************************************************************
{
  window_t box = getTextBoundaries(text);
  return box.height;
}
const unsigned int DisplayRegion::getTextWidth(const char* text)
{
  window_t box = getTextBoundaries(text);
  return box.width;
}
const DisplayRegion::window_t DisplayRegion::getTextBoundaries(const char* text)
{
    window_t box;
    display()->getTextBounds(text, 0, 0, &box.x, &box.y, &box.width, &box.height);
    return box;

}

