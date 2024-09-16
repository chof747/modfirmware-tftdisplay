#ifndef TFTDISPLAY_H
#define TFTDISPLAY_H

#include <Adafruit_ST7735.h> // Hardware-specific library #include <SPI.h>
#include <modfw_component.h>
#include "display_region.h"
#include <list>

#define ORIENT_UP_DOWN 0
#define ORIENT_RIGHT_LEFT 1
#define ORIENT_DOWN_UP 2
#define ORIENT_LEFT_RIGHT 3

namespace ModFirmWare
{

    class TFTDisplay : public Adafruit_ST7735, public Component
    {
    public:
        TFTDisplay(int8_t cs, int8_t dc, int8_t rsc);
        TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options);
        TFTDisplay(int8_t cs, int8_t dc, int8_t rsc, uint8_t options, uint8_t orientation);

        virtual size_t printlnStr(const char[]);
        virtual size_t printStr(const char[]);

        virtual bool setup(Application*);
        virtual void loop();

        size_t registerRegion(DisplayRegion* region);
        bool unregisterRegion(DisplayRegion* region);
        bool setBlinkFrequency(time_t blinkrate);

    private:
        uint8_t options;
        uint8_t orientation;
        bool blinkstate;
        time_t blinkfrequency;

        std::list<DisplayRegion*> regions;
    };

};

#endif // TFTDISPLAY_H