/**
 * @file buzzer.h
 * @brief TODO.
 *
 */


#ifndef BUZZER_H
#define BUZZER_H


typedef enum
{
    BUZZER_SOUND_OFF = 0,
    BUZZER_SOUND_ON,
    BUZZER_SOUND_SHORT_ONOFF,
    BUZZER_SOUND_LONG_ONOFF
} buzzer_sound_kind;


void buzzer_init(void);


void buzzer_sound(
        const buzzer_sound_kind sound);


#endif  /* PROTOCOL_H */
