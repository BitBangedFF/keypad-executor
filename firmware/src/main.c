/**
 * @file main.c
 * @brief Main.
 *
 */


#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include "board.h"
#include "usb_rawhid.h"
#include "time.h"
#include "key.h"
#include "keypad.h"


int main(void)
{
    keypad_s keypad;

    wdt_disable();

    led_init();
    led_off();

    time_init();

    enable_interrupt();

    keypad_init(&keypad);

    usb_init();

    time_delay_ms(1000);
    while(usb_configured() == 0)
    {
        led_toggle();
        time_delay_ms(50);
    }
    led_on();
    time_delay_ms(2000);
    led_off();

    while(1)
    {
        /*
        const uint8_t activity = keypad_get_keys(&keypad);

        if(activity != FALSE)
        {
            led_toggle();
        }
        */

        const uint8_t key = keypad_get_key(&keypad);

        if(key != (uint8_t) KEY_NONE)
        {
            led_toggle();
        }
    }

    return 0;
}
