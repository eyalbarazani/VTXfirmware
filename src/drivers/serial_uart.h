#pragma once

#define BAUD 9600
#define BAUDRATE F_CPU/16/BAUD-1

void uart_init(unsigned int baud_rate);
void uart_transmit_string(unsigned char data[]);
void uart_transmit_char(unsigned char data);
void uart_transmit_uint16(uint16_t n);