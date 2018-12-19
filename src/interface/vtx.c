#include "tbs_smartaudio.h"
#include "../drivers/eeprom.h"

#define EEPROM_TX_START_ADDR 0x00
#define EEPROM_BETAFLIGHT_PROTOCOL EEPROM_TX_START_ADDR
#define EEPROM_BAND EEPROM_TX_START_ADDR + 1
#define EEPROM_FREQ_H EEPROM_TX_START_ADDR + 2
#define EEPRON_FREQ_L EEPROM_TX_START_ADDR + 3
#define EEPROM_TRANSMIT_POWER EEPROM_TX_START_ADDR + 4

#define TBS_PROTOCOL 1

void vtx_set_all(uint8_t protocol, uint8_t band, uint16_t freq, uint8_t power)
{
	void vtx_set_protocol(protocol);
	void vtx_set_band(band);
	void vtx_set_freq(freq);
	void vtx_set_power(power);
}



uint8_t vtx_get_protocol()
{
	return EEPROM_read_byte(EEPROM_BETAFLIGHT_PROTOCOL);
}



uint8_t vtx_get_band()
{
	return EEPROM_read_byte(EEPROM_BAND);
}



uint16_t vtx_get_freq()
{
	return (EEPROM_read_byte(EEPROM_FREQ_H) << 8) + EEPROM_read_byte(EEPRON_FREQ_L);
}



uint8_t vtx_get_power()
{
	return EEPROM_read_byte(EEPROM_TRANSMIT_POWER);
}



void vtx_set_protocol(uint8_t protocol)
{
	EEPROM_write_byte(EEPROM_BETAFLIGHT_PROTOCOL, TBS_PROTOCOL);
}



void vtx_set_band(uint8_t band)
{
	EEPROM_write_byte(EEPROM_BAND, band);
}



void vtx_set_freq(uint16_t freq)
{
	EEPROM_write_byte(EEPROM_FREQ_H, freq >> 8);
	EEPROM_write_byte(EEPRON_FREQ_L, (freq << 8) >> 8);
}



void vtx_set_power(uint8_t power)
{
	EEPROM_write_byte(EEPROM_TRANSMIT_POWER, power);
}