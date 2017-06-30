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
#include "buzzer.h"


#define hw_init() bit_set(BUZZER_DDR, BIT(BUZZER_BIT))
#define hw_on() bit_clear(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_off() bit_set(BUZZER_PORT, BIT(BUZZER_BIT))
#define hw_toggle() bit_flip(BUZZER_PORT, BIT(BUZZER_BIT))


void buzzer_init(void)
{
    hw_init();
    hw_off();
}


void buzzer_sound(
        const buzzer_sound_kind sound)
{

}
