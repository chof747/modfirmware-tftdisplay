#ifndef DISPLAY_REGION_H
#define DISPLAY_REGION_H

#include <memory>
#include <Arduino.h>
#include <Adafruit_GFX.h>

namespace ModFirmWare
{

  typedef std::unique_ptr<uint16_t[]> imgbuffer_t;

  class TFTDisplay;

  class DisplayRegion
  {
  public:
    struct window_t
    {
      int x;
      int y;
      int width;
      int height;
    };

    DisplayRegion(const window_t window, TFTDisplay*  display) : 
      window(window), tft(display), blinking(false), canvas(window.width, window.height) {}

    virtual ~DisplayRegion() = default;
    void update(bool blink);
    virtual bool hasNewContent();

    // Getter and Setter for the Region struct
    inline void setWindow(const window_t &window) { this->window = window; }
    inline const window_t getWindow() const { return window; }

    inline bool isBlinking() { return blinking; }

  protected: 

    virtual void updateCanvas() = 0;
    virtual void doBlinking(bool blinkstate) { }

    inline const int width() const { return window.width; }
    inline const int height() const { return window.height; }

    virtual bool isUpdated() const = 0;

    Adafruit_GFX* display() { return &canvas; }


    bool blinking;

  private:
    window_t window;
    TFTDisplay* tft;
    GFXcanvas16 canvas;
  };

}

#endif // DISPLAY_REGION_H