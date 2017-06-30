/**
 * @file protocol.h
 * @brief TODO.
 *
 */


#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <stdint.h>


#define PROTO_MSG_SIZE (32)
#define PROTO_MSG_PREAMBLE (0xAFC3)
#define PROTO_KEYS_MAX (11)

#define PROTO_KEY_RESET '*'
#define PROTO_KEY_TERMINATE '#'


typedef struct __attribute__((packed))
{
    uint16_t preamble;
    uint32_t start_time;
    uint32_t end_time;
    uint16_t error_cnt;
    uint32_t reserved_0;
    uint16_t reserved_1;
    uint8_t key_cnt;
    uint8_t keys[PROTO_KEYS_MAX];
    uint16_t checksum;
} proto_msg_s;


#endif  /* PROTOCOL_H */
