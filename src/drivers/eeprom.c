#include <avr/io.h>

void EEPROM_write_byte(unsigned int uiAddress, unsigned char ucData)
{
	while(EECR & (1<<EEPE));
	EEAR = uiAddress;
	EEDR = ucData;
	EECR |= (1<<EEMPE);

	EECR |= (1<<EEPE);
}


unsigned char EEPROM_read_byte(unsigned int uiAddress)
{
	while(EECR & (1<<EEPE));
	EEAR = uiAddress;

	EECR |= (1<<EERE);

	return EEDR;
}