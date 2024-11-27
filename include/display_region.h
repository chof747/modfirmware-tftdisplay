#ifndef DISPLAY_REGION_H
#define DISPLAY_REGION_H

#include <memory>
#include <Arduino.h>

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

    DisplayRegion(const window_t window, TFTDisplay*  display) : window(window), tft(display), blinking(false) {}

    virtual ~DisplayRegion() = default;
    virtual void update(bool blink) = 0;
    virtual bool hasNewContent();

    // Getter and Setter for the Region struct
    inline void setWindow(const window_t &window) { this->window = window; }
    inline const window_t getWindow() const { return window; }

    inline bool isBlinking() { return blinking; }

  protected: 

    const int translateX(const int x) const;
    const int translateY(const int x) const;

    void drawImage(imgbuffer_t& buffer, int width, int height);
    
    inline const int width() const { return window.width; }
    inline const int height() const { return window.height; }

    virtual bool isUpdated() const = 0;

    TFTDisplay* display() { return tft; }

    bool blinking;

  private:
    window_t window;
    TFTDisplay* tft;
  };

}

#endif // DISPLAY_REGION_H