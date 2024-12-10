#include "tftdisplay.h"
#include "decodeutf8.h"
#include "gfxlatin1.h"
#include <Arduino.h>
#include <SPIFFS.h>
#include <memory>

using namespace ModFirmWare;

#ifndef BLINK_FREQUENCY
#define BLINK_FREQUENCY 1000
#endif

#define LOGTAG "tft"

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc)
//*****************************************************************************
    : Adafruit_ST7735(cs, dc, rsc),
      options(INITR_BLACKTAB),
      orientation(ORIENT_LEFT_RIGHT), regions(),
      backLightControl(false),
      backlightControlPin(255),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY),
      showAtStartup(nullptr)
{
}

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, int8_t bklPin, uint8_t options)
//*****************************************************************************
    : Adafruit_ST7735(cs, dc, rsc),
      options(options),
      orientation(ORIENT_RIGHT_LEFT), regions(),
      backLightControl(true),
      backlightControlPin(bklPin),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY),
      showAtStartup(nullptr)
{
}

TFTDisplay::TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, int8_t bklPin, uint8_t options, uint8_t orientation)
//*****************************************************************************
    : Adafruit_ST7735(cs, dc, rsc),
      options(options),
      orientation(orientation), regions(),
      backLightControl(true),
      backlightControlPin(bklPin),
      blinkstate(false),
      blinkfrequency(BLINK_FREQUENCY),
      showAtStartup(nullptr)
{
}

bool TFTDisplay::setup(Application *app)
//*****************************************************************************
{
    if (Component::setup(app))
    {
        this->initR(options);
        this->setRotation(orientation);

        fillScreen(ST7735_BLACK);
        logger->debug(LOGTAG, "Display Width = %d, Height = %d", width(), height());
        configureBacklight();

        if (nullptr != showAtStartup)
        {
            showAtStartup->update(false);
        }


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

void TFTDisplay::enableSleep(bool enable)
//*****************************************************************************
{
    Adafruit_ST7735::enableSleep(enable);

    if (backLightControl)
    {
        // 100ms delay is avoiding a white flash when turning backlight back on
        if (!enable)
            delay(100);
        digitalWrite(backlightControlPin, !enable ? HIGH : LOW);
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
            DisplayRegion::window_t w = (*it)->getWindow();
            fillRect(w.x, w.y, w.width, w.height, ST7735_BLACK);
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

void TFTDisplay::setShowAtStartup(DisplayRegion * region)
//*****************************************************************************
{
    showAtStartup = region;
}

const DisplayRegion::window_t TFTDisplay::getWindow()
//*****************************************************************************
{
    return DisplayRegion::window_t({
        x : 0,
        y : 0,
        width : (uint16_t) width(),
        height : (uint16_t) height()
    });
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

imgbuffer_t TFTDisplay::loadImageFromSPIFFS(const char *filename, int width, int height)
//*****************************************************************************
{
    // allocate the image buffer
    std::unique_ptr<uint16_t[]> buffer(new uint16_t[width * height]);

    File file = SPIFFS.open(filename, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return nullptr;
    }

    int y = 0;
    /*
    while (file.available() && y < height)
    {
        file.read(reinterpret_cast<uint8_t *>(buffer.get() + y * width), width * 2);
        y++;
    }
    */
    file.read(reinterpret_cast<uint8_t *>(buffer.get()), height * width * 2);
    file.close();

    return buffer;
}

void ModFirmWare::TFTDisplay::configureBacklight()
//*****************************************************************************
{
    if (backLightControl && (255 != backlightControlPin))
    {

        pinMode(backlightControlPin, OUTPUT);
        digitalWrite(backlightControlPin, HIGH);
    }
}
