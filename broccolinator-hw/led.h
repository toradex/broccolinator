#ifndef LED_H
#define LED_H

#include <gpiod.h>

class LED
{
private:
    gpiod_line *led_gpio;
    gpiod_chip *led_chip;

public:
    // configures devices using the selected pins
    LED();
    ~LED();

    bool init(const char *led_pin_name);
    void set_state(bool state);

};

#endif
