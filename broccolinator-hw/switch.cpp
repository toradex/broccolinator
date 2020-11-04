#include "switch.h"
#include "unistd.h"

Switch::Switch()
{
    switch_gpio = NULL;
    switch_chip=NULL;
}

Switch::~Switch()
{
    if (switch_gpio)
    {
        gpiod_line_release(switch_gpio);
    }

    if (switch_chip)
    {
        gpiod_chip_close(switch_chip);
    }
}

bool Switch::init(const char *switch_pin_name)
{
    char switch_chip_name[32];
    unsigned int switch_offset;

    if (gpiod_ctxless_find_line(switch_pin_name, switch_chip_name, 32, &switch_offset) != 1)
    {
        return false;
    }

    switch_chip = gpiod_chip_open_by_name(switch_chip_name);

    if (!switch_chip)
    {
        return false;
    }

    switch_gpio = gpiod_chip_get_line(switch_chip, switch_offset);

    if (!switch_gpio)
    {
        return false;
    }

    if (gpiod_line_request_rising_edge_events(switch_gpio,"broccolinator-hw-switch-gpio"))
    {
        return false;
    }
    return true;
}

int Switch::get_fd()
{
    return gpiod_line_event_get_fd(switch_gpio);
}

void Switch::clear_event()
{
    gpiod_line_event event;

    // debounce for 80ms
    usleep(80000);

    int fd =get_fd();

    fd_set rdfs;

    FD_ZERO(&rdfs);

    FD_SET(fd,&rdfs);

    timeval timeout={.tv_sec=0, .tv_usec=1};

    // clean the events still in buffer, to avoid noise
    while (select(FD_SETSIZE,&rdfs,NULL,NULL,&timeout)!=0)
    {
        gpiod_line_event_read_fd(fd,&event);
        FD_SET(fd,&rdfs);
    }        
}