#include "unity/src/unity.h"
#include "../src/interface/tbs_smartaudio.h"

/* example host messages from manual */
uint8_t get_settings_example[] = {0xAA, 0x55, 0x03, 0x00, 0x9F};
uint8_t set_power_example[] = {0xAA, 0x55, 0x05, 0x01, 0x00, 0x6B};
uint8_t set_channel_example[] = {0xAA, 0x55, 0x07, 0x01, 0x00, 0xB8};
uint8_t set_frequency_example[] = {0xAA, 0x55, 0x09, 0x02, 0x16, 0xE9, 0xDC};
uint8_t wrong_crc[] = {0xAA, 0x55, 0x09, 0x02, 0x16, 0xE9, 0xDD};


void test_crc8_different_inputs(void)
{
	uint8_t m1[] = {0x23};
	uint8_t m2[] = {0xD5, 0x7F};
	uint8_t m3[] = {0x5C, 0x08, 0xDD};
	uint8_t m4[] = {0x65, 0x31, 0xE4, 0x4E};
	uint8_t m5[] = {0xC4, 0x6E, 0xBB, 0xC6, 0x13};

	TEST_ASSERT_EQUAL_HEX8(0xE, crc8(m1, 1));
	TEST_ASSERT_EQUAL_HEX8(0x95, crc8(m2, 2));
	TEST_ASSERT_EQUAL_HEX8(0x92, crc8(m3, 3));
	TEST_ASSERT_EQUAL_HEX8(0xDA, crc8(m4, 4));
	TEST_ASSERT_EQUAL_HEX8(0x1C, crc8(m5, 5));
	TEST_ASSERT_EQUAL_HEX8(0x6B, crc8(set_power_example, 5));
}


void test_host_to_vtx_cmd_unshift(void)
{
	TEST_ASSERT_EQUAL_HEX8(TBS_GET_SETTINGS, host_to_vtx_cmd_unshift(0x03));
	TEST_ASSERT_EQUAL_HEX8(TBS_SET_POWER, host_to_vtx_cmd_unshift(0x05));
	TEST_ASSERT_EQUAL_HEX8(TBS_SET_CHANNEL, host_to_vtx_cmd_unshift(0x07));
	TEST_ASSERT_EQUAL_HEX8(TBS_SET_FREQUENCY, host_to_vtx_cmd_unshift(0x09));
}

void test_tbs_verify_crc8(void)
{
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_verify_crc8(get_settings_example), "get_settings_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_verify_crc8(set_power_example), "set_power_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_verify_crc8(set_channel_example), "set_channel_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_verify_crc8(set_frequency_example), "set_frequency_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(0, tbs_verify_crc8(wrong_crc), "wrong_crc_example");
}

void test_tbs_parse_host_msg(void)
{
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_host_msg_parsing(get_settings_example), "get_settings_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_host_msg_parsing(set_power_example), "set_power_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_host_msg_parsing(set_channel_example), "set_channel_example");
	TEST_ASSERT_EQUAL_HEX8_MESSAGE(1, tbs_host_msg_parsing(set_frequency_example), "set_frequency_example");
}

void test_tbs_compose_frame(void)
{
	struct tbs_frame frame = {
		.command = (TBS_SET_FREQUENCY << 1) + 1,
		.payload = {0x16, 0xE9},
		.data_length = 0x02
		};
	uint8_t data[12];
	uint8_t data_length = tbs_compose_frame(data, frame);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(set_frequency_example, data, data_length);
	TEST_ASSERT_EQUAL_UINT8(7, data_length);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_crc8_different_inputs);
	RUN_TEST(test_host_to_vtx_cmd_unshift);
	RUN_TEST(test_tbs_verify_crc8);
	RUN_TEST(test_tbs_parse_host_msg);
	RUN_TEST(test_tbs_compose_frame);
	return UNITY_END();
}
