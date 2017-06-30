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
#include "buzzer.h"
#include "protocol.h"
#include "transport.h"


static void wait_for_transport(void)
{
    time_delay_ms(1000);
    while(transport_ready() == 0)
    {
        led_toggle();
        time_delay_ms(50);
    }
    led_on();
    time_delay_ms(1000);
    led_off();
}


static void init_msg(
        const uint16_t error_cnt,
        proto_msg_s * const msg)
{
    (void) memset(msg, 0, sizeof(*msg));
    msg->preamble = PROTO_MSG_PREAMBLE;
    msg->error_cnt = error_cnt;
}


static void on_key(
        const uint8_t key,
        proto_msg_s * const msg)
{
    msg->end_time = time_get_ms();
    msg->keys[msg->key_cnt] = key;
    msg->key_cnt += 1;

    if(msg->key_cnt == 1)
    {
        msg->start_time = msg->end_time;
    }

    if(key == (uint8_t) PROTO_KEY_TERMINATE)
    {
        if(msg->key_cnt > 1)
        {
            msg->checksum = protocol_crc16(msg);
        
            if(transport_send(msg) != 0)
            {
                msg->error_cnt += 1;
            }

            buzzer_sound(BUZZER_SOUND_LONG_ONOFF);
        }

        init_msg(msg->error_cnt, msg);
    }
    else if(key == (uint8_t) PROTO_KEY_RESET)
    {
        buzzer_sound(BUZZER_SOUND_ERROR);
        init_msg(msg->error_cnt, msg);
    }
    else
    {
        buzzer_sound(BUZZER_SOUND_SHORT_ONOFF);
    }

    if(msg->key_cnt >= PROTO_KEYS_MAX)
    {
        buzzer_sound(BUZZER_SOUND_ERROR);
        init_msg(msg->error_cnt, msg);
    }
}


int main(void)
{
    keypad_s keypad;
    proto_msg_s msg;

    wdt_disable();

    led_init();
    led_off();

    init_msg(0, &msg);

    time_init();

    buzzer_init();

    enable_interrupt();

    keypad_init(&keypad);

    transport_init();

    wait_for_transport();

    while(1)
    {
        const uint8_t key = keypad_get_key(&keypad);

        if(key != (uint8_t) KEY_NONE)
        {
            on_key(key, &msg);
        }
    }

    return 0;
}
