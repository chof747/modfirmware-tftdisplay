#include "display_region.h"

using namespace ModFirmWare;

bool DisplayRegion::hasNewContent()
//****************************************************************************************
{
  return active && isUpdated();
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