/**
 * @file buzzer.c
 * @brief TODO.
 *
 */


#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>

#include "board.h"
#include "time.h"
#include "buzzer.h"


#define BUZZER_OFF (1)

#define hw_init() bit_set(BUZZER_DDR, BIT(BUZZER_BIT))

#ifdef BUZZER_OFF
#warning "buzzer is disabled"
#define hw_on() bit_set(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_off() bit_set(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_toggle() bit_set(BUZZER_PORT, BIT(BUZZER_BIT))
#else
#define hw_on() bit_clear(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_off() bit_set(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_toggle() bit_flip(BUZZER_PORT, BIT(BUZZER_BIT))
#endif


void buzzer_init(void)
{
    hw_init();
    hw_off();
}


void buzzer_sound(
        const buzzer_sound_kind sound)
{
    if(sound == BUZZER_SOUND_OFF)
    {
        hw_off();
        led_off();
    }
    else if(sound == BUZZER_SOUND_ON)
    {
        hw_on();
        led_on();
    }
    else if(sound == BUZZER_SOUND_ERROR)
    {
        uint8_t i;
        for(i = 0; i < 3; i += 1)
        {
            hw_on();
            led_on();
            time_delay_ms(100);
            hw_off();
            led_off();
            time_delay_ms(100);
        }
        hw_off();
        led_off();
    }
    else if(sound == BUZZER_SOUND_SHORT_ONOFF)
    {
        hw_on();
        led_on();
        time_delay_ms(200);
        hw_off();
        led_off();
    }
    else if(sound == BUZZER_SOUND_LONG_ONOFF)
    {
        hw_on();
        led_on();
        time_delay_ms(800);
        hw_off();
        led_off();
    }
}
