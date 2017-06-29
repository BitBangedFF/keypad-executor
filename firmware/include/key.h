/**
 * @file key.h
 * @brief TODO.
 *
 */


#ifndef KEY_H
#define KEY_H


#include <stdint.h>


typedef enum
{
    KEY_STATE_IDLE = 0,
    KEY_STATE_PRESSED,
    KEY_STATE_HOLD,
    KEY_STATE_RELEASED,
    KEY_STATE_KIND_COUNT
} key_state_kind;


typedef struct
{
    char kchar;
    uint8_t kcode;
    key_state_kind state;
    uint8_t state_changed;
} key_s;


extern const char KEY_NONE;
extern const uint8_t KEY_CODE_INVALID;


void key_new(
        key_s * const key);


void key_init(
        const char kchar,
        key_s * const key);


void key_update(
        const char kchar,
        const key_state_kind state,
        const uint8_t status,
        key_s * const key);


#endif  /* KEY_H */
