#pragma once
#include <stdint.h>

#define TBS_SYNC_BYTE 0xAA
#define TBS_HEADER_BYTE 0x55

#define TBS_GET_SETTINGS 0x01
#define TBS_SET_POWER 0x02
#define TBS_SET_CHANNEL 0x03
#define TBS_SET_FREQUENCY 0x04
#define TBS_SET_OPERATION_MODE 0x05

typedef struct tbs_frame
{
	uint8_t command;
	uint8_t data_length;
	uint8_t payload[10];
	uint8_t crc8;
} tbs_frame;


uint8_t crc8(const uint8_t *data, uint8_t data_length);
uint8_t host_to_vtx_cmd_unshift(uint8_t cmd);
uint8_t tbs_host_msg_parsing(uint8_t *raw_data);
uint8_t tbs_verify_crc8(uint8_t *raw_data);
uint8_t tbs_compose_frame(uint8_t data[], tbs_frame frame);