/**
 * @file key.c
 * @brief TODO.
 *
 */


#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include "key.h"


const char KEY_NONE = '\0';
const uint8_t KEY_CODE_INVALID = 0xFF;


void key_new(
        key_s * const key)
{
    key->kchar = KEY_NONE;
    key->kcode = KEY_CODE_INVALID;
    key->state = KEY_STATE_IDLE;
    key->state_changed = 0;
}


void key_init(
        const char kchar,
        key_s * const key)
{
    key_new(key);
    key->kchar = kchar;
}


void key_update(
        const char kchar,
        const key_state_kind state,
        const uint8_t status,
        key_s * const key)
{
    key->kchar = kchar;
    key->state = state;
    key->state_changed = status;
}
