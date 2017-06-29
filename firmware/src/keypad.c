/**
 * @file keypad.c
 * @brief TODO.
 *
 */


#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include "board.h"
#include "key.h"
#include "keypad.h"


#define NUM_ROWS (4)
#define NUM_COLS (3)


static const char KEY_MAP[NUM_ROWS][NUM_COLS] =
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

static const uint8_t ROW_PINS[NUM_ROWS] =
{
    6, 5, 4, 3
};

static const uint8_t COL_PINS[NUM_COLS] =
{
    2, 1, 0
};


static void pin_conf_output(
        const uint8_t pin)
{

}


static void pin_conf_input(
        const uint8_t pin)
{

}


static void pin_conf_input_pullup(
        const uint8_t pin)
{

}


static void pin_output(
        const uint8_t pin,
        const uint8_t state)
{

}


static uint8_t pin_read(
        const uint8_t pin)
{
    return 0;
}


static uint8_t find_in_list(
        const uint8_t kchar,
        keypad_s * const keypad)
{
    uint8_t ret = KEY_CODE_INVALID;

    uint8_t idx;
    for(idx = 0; (idx < KEYPAD_LIST_MAX) && (ret == KEY_CODE_INVALID); idx += 1)
    {
        if(keypad->keys[idx].kchar == kchar)
        {
            ret = idx;
        }
    }

    return ret;
}


static void next_key_state(
        const uint8_t idx,
        const uint8_t pressed,
        keypad_s * const keypad)
{
#warning "TODO"
}


static void scan_keys(
        keypad_s * const keypad)
{
    uint8_t row;
    for(row = 0; row < keypad->size.rows; row += 1)
    {
        pin_conf_input_pullup(ROW_PINS[row]);
    }

    uint8_t col;
    for(col = 0; col < keypad->size.columns; col += 1)
    {
        pin_conf_output(COL_PINS[col]);
        pin_output(COL_PINS[col], LOW);

        for(row = 0; row < keypad->size.rows; row += 1)
        {
           bit_write(
                   !pin_read(ROW_PINS[row]),
                   keypad->bit_map[row],
                   BIT(col));
        }

        pin_output(COL_PINS[col], HIGH);
        pin_conf_input(COL_PINS[col]);
    }
}


static uint8_t update_list(
        keypad_s * const keypad)
{
    uint8_t activity = 0;

    uint8_t idx;
    for(idx = 0; idx < KEYPAD_LIST_MAX; idx += 1)
    {
        if(keypad->keys[idx].state == KEY_STATE_IDLE)
        {
            keypad->keys[idx].kchar = KEY_NONE;
            keypad->keys[idx].kcode = KEY_CODE_INVALID;
            keypad->keys[idx].state_changed = 0;
        }
    }

    uint8_t row;
    for(row = 0; row < keypad->size.rows; row += 1)
    {
        uint8_t col;
        for(col = 0; col < keypad->size.columns; col += 1)
        {
            const uint8_t btn_pressed = bit_get(keypad->bit_map[row], BIT(col));
            const uint8_t kcode = row * keypad->size.columns + col;
            const char kchar = keypad->key_map[kcode];
            const uint8_t k_idx = find_in_list(kcode, keypad);

            // already in the list, update its state
            if(k_idx != KEY_CODE_INVALID)
            {
                next_key_state(k_idx, btn_pressed, keypad);
            }
            else if((idx == KEY_CODE_INVALID) && (btn_pressed != 0))
            {
                for(idx = 0; idx < KEYPAD_LIST_MAX; idx += 1)
                {
                    if(keypad->keys[idx].kchar == KEY_NONE)
                    {
                        keypad->keys[idx].kchar = kchar;
                        keypad->keys[idx].kcode = kcode;
                        keypad->keys[idx].state = KEY_STATE_IDLE;

                        next_key_state(idx, btn_pressed, keypad);

                        // only fill the single key
                        break;
                    }
                }
            }
        }
    }

    for(idx = 0; idx < KEYPAD_LIST_MAX; idx += 1)
    {
        if(keypad->keys[idx].state_changed != 0)
        {
            activity = 1;
        }
    }

    return activity;
}


void keypad_init(
        keypad_s * const keypad)
{
    (void) memset(keypad, 0, sizeof(*keypad));

    keypad->key_map = (const char*) KEY_MAP;
    keypad->size.rows = NUM_ROWS;
    keypad->size.columns = NUM_COLS;
    
    keypad->single_key = 0;

    uint8_t idx;
    for(idx = 0; idx < KEYPAD_LIST_MAX; idx += 1)
    {   
        key_new(&keypad->keys[idx]);
    }
}


uint8_t keypad_get_keys(
        keypad_s * const keypad)
{
#warning "TODO"
    return 0;
}
