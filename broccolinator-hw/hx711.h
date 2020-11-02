#ifndef HX711_H
#define HX711_H

#include <gpiod.h>

class HX711
{
private:
    gpiod_line *data_gpio;
    gpiod_line *clock_gpio;

    gpiod_chip *data_chip;
    gpiod_chip *clock_chip;

    int tare;

    // this has been calibrated for a 3Kg load cell
    const double conversion_rate = 655.0;

public:
    // configures devices using the selected pins
    HX711();
    ~HX711();

    bool init(const char *data_pin_name, const char *clock_pin_name);

    // returns weight in grams
    int read_weight();

protected:
    bool is_ready();
    void toggle_clock();
    int shift_in_bit();
    int read_adc_value();    
};

#endif
