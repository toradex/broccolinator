#include <iostream>
#include <sys/select.h>
#include "broccolinator-hw.h"
#include "hx711.h"
#include "led.h"
#include "switch.h"
#include "commandsocket.h"
#include "unistd.h"

//#define COLIBRI
//#define VERDIN
#define APALIS

int main(int argc, char const *argv[])
{
    CommandSocket   cmdsocket=CommandSocket();
    HX711           hx711 = HX711();
    LED             ok_led=LED();
    LED             ko_led=LED();
    Switch          sw=Switch();

    if (!cmdsocket.init())
    {
        printf("Error initializing communication channel.\n");       
        return -1;
    }

#if defined(COLIBRI)
    hx711.init("SODIMM_96", "SODIMM_97");
#elif defined (VERDIN)
    hx711.init("SODIMM_210", "SODIMM_212");
#elif defined (APALIS)
    if (!hx711.init("MXM3_3/GPIO2", "MXM3_5/GPIO3") ||
        !ok_led.init("MXM3_7/GPIO4") ||
        !ko_led.init("MXM3_13/GPIO6") ||
        !sw.init("MXM3_1/GPIO1"))
    {
        printf("Error initializing hardware.\n");       
        return -1;
    }
#endif

    printf("broccolinator-hw started.\n");  
    fflush(stdout);
    
    fd_set rdfs;

    FD_ZERO(&rdfs);

    FD_SET(cmdsocket.get_fd(),&rdfs);
    FD_SET(sw.get_fd(),&rdfs);

    while (select(FD_SETSIZE,&rdfs,NULL,NULL,NULL)>0)
    {
        if (FD_ISSET(cmdsocket.get_fd(),&rdfs))
        {
            switch(cmdsocket.get_command())
            {
                case CMD_CONNECT:
                    printf("Client connected.\n");
                    fflush(stdout);
                    break;
                case CMD_OK:
                    printf("OK.\n");
                    fflush(stdout);
                    ok_led.set_state(true);
                    ko_led.set_state(false);
                    break;
                case CMD_KO:
                    printf("KO.\n");
                    fflush(stdout);
                    ok_led.set_state(false);
                    ko_led.set_state(true);
                    break;
                case CMD_PROCESSING:
                    ok_led.set_state(false);
                    ko_led.set_state(false);
                    break;
                case CMD_WEIGHT:
                    {
                        printf("Weight requested.\n");
                        fflush(stdout);

                        EVENT_DATA evt;

                        evt.event=EVT_WEIGHT;
                        evt.weight.weight=hx711.read_weight();

                        printf("Weight: %dg\n",evt.weight.weight);
                        fflush(stdout);

                        cmdsocket.send_event(&evt);
                    }
            }
        }       
        if (FD_ISSET(sw.get_fd(),&rdfs))
        {
            sw.clear_event();

            printf("Sending start event.\n");
            fflush(stdout);

            EVENT_DATA evt;

            evt.event=EVT_START;

            if (!cmdsocket.send_event(&evt))
            {
                printf("Error sending event.\n");       
                fflush(stdout);
                return -1;
            }            
        }

        FD_SET(sw.get_fd(),&rdfs);
        FD_SET(cmdsocket.get_fd(),&rdfs);       
    }

    return 0;
}
