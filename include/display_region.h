#ifndef DISPLAY_REGION_H
#define DISPLAY_REGION_H

#include <memory>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "logengine.h"

namespace ModFirmWare
{

  typedef std::unique_ptr<uint16_t[]> imgbuffer_t;

  class TFTDisplay;

  class DisplayRegion
  {
  public:
    struct window_t
    {
      int16_t x;
      int16_t y;
      uint16_t width;
      uint16_t height;
    };

    DisplayRegion(const window_t window, TFTDisplay*  display, const char* caption = "") : 
      window(window), tft(display), blinking(false), canvas(window.width, window.height), 
      logger(LogEngine::getInstance()), caption(caption) {}

    virtual ~DisplayRegion() = default;
    void update(bool blink);
    virtual bool hasNewContent();

    // Getter and Setter for the Region struct
    inline void setWindow(const window_t &window) { this->window = window; }
    inline const window_t getWindow() const { return window; }

    inline bool isBlinking() { return blinking; }

    inline const char* getCaption() { return caption; }
    Adafruit_GFX* display() { return &canvas; }
    const unsigned int getTextHeight(const char* text);
    const unsigned int getTextWidth(const char* text);

  protected: 

    virtual void updateCanvas() = 0;
    virtual void doBlinking(bool blinkstate) { }

    inline const int width() const { return window.width; }
    inline const int height() const { return window.height; }

    const window_t getTextBoundaries(const char* text);

    virtual bool isUpdated() const = 0;

    LogEngine* logger;

    bool blinking;

  private:
    window_t window;
    TFTDisplay* tft;
    GFXcanvas16 canvas;
    const char* caption;
  };

}

#endif // DISPLAY_REGION_H