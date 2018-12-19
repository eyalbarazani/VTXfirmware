#define F_CPU 16000000

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

#include "drivers/serial_uart.h"
#include "drivers/eeprom.h"
#include "interface/vtx.h"

int main()
{
	uart_init(BAUDRATE);
	
	DDRB = 1<<PORTB5;

	if (vtx_get_protocol() != 1)
	{
		uart_transmit_string((unsigned char *) "Writing vtx settings to EEPROM!\r\n");
		vtx_set_all(1, 'E', 5836, 3);
	}

	while (1)
	{
		PORTB ^= 1<<PORTB5;

		if (PORTB & 1 << PORTB5)
		{
			uart_transmit_string((unsigned char *) "VTX protocol: ");
			uart_transmit_uint16(vtx_get_protocol());
			uart_transmit_string((unsigned char *) "\r\n");

			uart_transmit_string((unsigned char *) "VTX band: ");
			uart_transmit_char(vtx_get_band());
			uart_transmit_string((unsigned char *) "\r\n");

			uart_transmit_string((unsigned char *) "VTX channel: ");
			uart_transmit_uint16(vtx_get_freq());
			uart_transmit_string((unsigned char *) "\r\n");

			uart_transmit_string((unsigned char *) "VTX power: ");
			uart_transmit_uint16(vtx_get_power());
			uart_transmit_string((unsigned char *) "\r\n");
		}
		_delay_ms(2000);
	}
	return 0;
}