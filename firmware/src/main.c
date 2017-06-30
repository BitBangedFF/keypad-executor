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

    while(1)
    {
        const uint8_t activity = keypad_get_keys(&keypad);

        if(activity != FALSE)
        {
            //led_toggle();
            led_on();
        }
    }

    return 0;
}
