#include "led.h"

LED::LED()
{
    led_gpio = NULL;    
    led_chip=NULL;    
}

LED::~LED()
{
    if (led_gpio)
    {
        gpiod_line_release(led_gpio);
    }

    if (led_chip)
    {
        gpiod_chip_close(led_chip);
    }

}

bool LED::init(const char *led_pin_name)
{
    char led_chip_name[32];
    unsigned int led_offset;

    if (gpiod_ctxless_find_line(led_pin_name, led_chip_name, 32, &led_offset) != 1)
    {
        return false;
    }

    led_chip = gpiod_chip_open_by_name(led_chip_name);

    if (!led_chip)
    {
        return false;
    }

    led_gpio = gpiod_chip_get_line(led_chip, led_offset);

    if (!led_gpio)
    {
        return false;
    }
      
    if (gpiod_line_request_output(led_gpio,"broccolinator-hw-led-gpio",0))
    {
        return false;
    }
    
    if (gpiod_line_set_value(led_gpio, 0))
    {
        return false;
    }
    return true;
}

void LED::set_state(bool state)
{
    gpiod_line_set_value(led_gpio,state?1:0);
}

