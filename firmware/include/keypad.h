/**
 * @file keypad.h
 * @brief TODO.
 *
 */


#ifndef KEYPAD_H
#define KEYPAD_H


#include <stdint.h>

#include "key.h"


#define KEYPAD_LIST_MAX (10)
#define KEYPAD_MAP_LEN (10)


typedef struct
{
    uint8_t rows;
    uint8_t columns;
} keypad_size_s;


typedef struct
{
    const char *key_map;
    keypad_size_s size;
    uint32_t debounce_time;
    uint32_t hold_time;
    uint32_t hold_timer;
    uint32_t start_time;
    uint16_t bit_map[KEYPAD_MAP_LEN];
    key_s keys[KEYPAD_LIST_MAX];
} keypad_s;


void keypad_init(
        keypad_s * const keypad);


uint8_t keypad_get_keys(
        keypad_s * const keypad);


#endif  /* KEYPAD_H */
