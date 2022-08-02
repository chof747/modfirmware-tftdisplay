#ifndef TFTDISPLAY_H
#define TFTDISPLAY_H

#include <Adafruit_ST7735.h> // Hardware-specific library #include <SPI.h>
#include <component.h>

#define ORIENT_UP_DOWN 0
#define ORIENT_RIGHT_LEFT 1
#define ORIENT_DOWN_UP 2
#define ORIENT_LEFT_RIGHT 3

namespace ModFirmWare
{

    class TFTDisplay : public Adafruit_ST7735, public Component
    {
    public:
        TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc);
        TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc, uint8_t options);
        TFTDisplay(gpio_num_t cs, gpio_num_t dc, gpio_num_t rsc, uint8_t options, uint8_t orientation);

        virtual size_t printlnStr(const char[]);
        virtual size_t printStr(const char[]);

        virtual bool setup();
        virtual void loop();

    private:
        uint8_t options;
        uint8_t orientation;
    };

};

#endif // TFTDISPLAY_H