#ifndef SWITCH_H
#define SWITCH_H

#include <gpiod.h>

class Switch
{
private:
    gpiod_line *switch_gpio;
    gpiod_chip *switch_chip;

public:
    // configures devices using the selected pins
    Switch();
    ~Switch();

    bool init(const char *switch_pin_name);

    // return fd for select
    int get_fd();

    // prepares to receive next event
    void clear_event();    
};

#endif
