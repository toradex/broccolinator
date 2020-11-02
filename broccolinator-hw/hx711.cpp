#include "hx711.h"
#include "unistd.h"

HX711::HX711()
{
    data_gpio = NULL;
    clock_gpio = NULL;    
    data_chip=NULL;
    clock_chip=NULL;    
}

HX711::~HX711()
{
    if (data_gpio)
    {
        gpiod_line_release(data_gpio);
    }

    if (clock_gpio)
    {
        gpiod_line_release(clock_gpio);
    }

   if (data_chip)
    {
        gpiod_chip_close(data_chip);
    }

    if (clock_chip)
    {
        gpiod_chip_close(clock_chip);
    }

}

bool HX711::init(const char *data_pin_name, const char *clock_pin_name)
{
    char data_chip_name[32];
    char clock_chip_name[32];
    unsigned int data_offset;
    unsigned int clock_offset;

    if (gpiod_ctxless_find_line(data_pin_name, data_chip_name, 32, &data_offset) != 1)
    {
        return false;
    }

    if (gpiod_ctxless_find_line(clock_pin_name, clock_chip_name, 32, &clock_offset) != 1)
    {
        return false;
    }

    data_chip = gpiod_chip_open_by_name(data_chip_name);

    if (!data_chip)
    {
        return false;
    }

    clock_chip = gpiod_chip_open_by_name(clock_chip_name);

    if (!clock_chip)
    {
        return false;
    }

    data_gpio = gpiod_chip_get_line(data_chip, data_offset);

    if (!data_gpio)
    {
        return false;
    }

    clock_gpio = gpiod_chip_get_line(clock_chip, clock_offset);

    if (!clock_gpio)
    {
        return false;
    }

    gpiod_line_request_config data_req = {
            .consumer="broccolinator-hw-hx711-data",
            .request_type= GPIOD_LINE_REQUEST_DIRECTION_INPUT,
            .flags = 0
       };
       
    gpiod_line_request_config clock_req = {
            .consumer="broccolinator-hw-hx711-data",
            .request_type= GPIOD_LINE_REQUEST_DIRECTION_OUTPUT,
            .flags = 0 | GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN
       };

    if (gpiod_line_request(data_gpio,&data_req,0))
    {
        return false;
    }

    if (gpiod_line_request(clock_gpio,&clock_req,0))
    {
        return false;
    }

    if (gpiod_line_set_value(clock_gpio, 0))
    {
        return false;
    }

    tare = read_adc_value();

    return true;
}

bool HX711::is_ready()
{
    int state=gpiod_line_get_value(data_gpio);
    
    return state ? false : true;
}

void HX711::toggle_clock()
{
    // delay loop is ugly, but any sleep function won't work there to grant pulses of 1us up to 50us using
    // the standard kernel and we want the demo to run on standard images of Torizon
    int delay_count=1000;

    gpiod_line_set_value(clock_gpio, 1);
    for (int i=0;i<delay_count;i++);
    gpiod_line_set_value(clock_gpio, 0);
    for (int i=0;i<delay_count;i++);
}

int HX711::shift_in_bit()
{
    toggle_clock();
    return gpiod_line_get_value(data_gpio);
}

int HX711::read_adc_value()
{
    int value = 0;    
    
    while (!is_ready()) {
        usleep(10);
    }

    for (int i = 0; i < 24; i++)
    {
        value = value << 1;
        value |= shift_in_bit();
    }

    toggle_clock();

    if (value & 0x00800000) {
       value=0xFF000000 | value; 
    }

    return value;
}

int HX711::read_weight()
{
    const int samples = 3;

    int int_value = 0;

    for (int i = 0; i < samples; i++)
    {
        int_value += read_adc_value() - tare;
    }

    double value = ((double)int_value) / 3;

    value/=conversion_rate;

    return (int)value;
}
