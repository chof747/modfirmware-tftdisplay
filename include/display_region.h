#ifndef DISPLAY_REGION_H
#define DISPLAY_REGION_H

namespace ModFirmWare
{

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

    DisplayRegion(const window_t window, TFTDisplay*  display) : window(window), tft(display), active(true) {}

    virtual ~DisplayRegion() = default;
    virtual void update() = 0;
    virtual bool hasNewContent();

    // Getter and Setter for the Region struct
    inline void setWindow(const window_t &window) { this->window = window; }
    inline const window_t getWindow() const { return window; }

    inline void activate() { active = true; }
    inline void deactivate() { active = false; }

  protected: 

    const int translateX(const int x) const;
    const int translateY(const int x) const;

    inline const int width() const { return window.width; }
    inline const int height() const { return window.height; }

    virtual bool isUpdated() const = 0;

    TFTDisplay* display() { return tft; }

    bool active;

  private:
    window_t window;
    TFTDisplay* tft;
  };

}

#endif // DISPLAY_REGION_H