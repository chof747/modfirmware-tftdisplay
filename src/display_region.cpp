#include "display_region.h"
#include <Arduino.h>
#include "tftdisplay.h"

using namespace ModFirmWare;

void DisplayRegion::update(bool blink)
//****************************************************************************************
{
  if (isUpdated())
  {
    updateCanvas();
  }

  doBlinking(blink);
  tft->drawRGBBitmap(window.x,window.y, canvas.getBuffer(), canvas.width(), canvas.height());
}

bool DisplayRegion::hasNewContent()
//****************************************************************************************
{
  return isUpdated();
}
