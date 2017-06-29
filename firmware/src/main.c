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
    led_on();

    time_init();

    enable_interrupt();

    while(1)
    {
        //time_delay_ms(500);
        //led_toggle();
    }

    return 0;
}
