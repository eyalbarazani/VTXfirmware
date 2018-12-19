#include <avr/io.h>
#include "serial_uart.h"


void uart_init(unsigned int baud_rate)
{
	UBRR0H = (unsigned char) (baud_rate >> 8);
	UBRR0L = (unsigned char) baud_rate;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	return;
}


void uart_transmit_char(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));

	UDR0 = data;
}

void uart_transmit_string(unsigned char data[])
{
	int i = 0;
	while (data[i] != '\0')
	{
		uart_transmit_char(data[i]);
		i++;
	}
}



unsigned char num_to_char(uint8_t n)
{
	switch (n)
	{
		case 0:
		return 0;
		break;
		case 1:
		return '1';
		break;
		case 2:
		return '2';
		break;
		case 3:
		return '3';
		break;
		case 4:
		return '4';
		break;
		case 5:
		return '5';
		break;
		case 6:
		return '6';
		break;
		case 7:
		return '7';
		break;
		case 8:
		return '8';
		break;
		case 9:
		return '9';
		break;
	}
	return 0;
}



void uart_transmit_uint16(uint16_t n)
{
	while (n > 0)
	{
		uart_transmit_char(num_to_char(n % 10));
		n /= 10;
	}
}