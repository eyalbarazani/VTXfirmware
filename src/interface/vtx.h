#pragma once

void vtx_set_all(uint8_t protocol, uint8_t band, uint16_t freq, uint8_t power);

uint8_t vtx_get_protocol();
uint8_t vtx_get_band();
uint16_t vtx_get_freq();
uint8_t vtx_get_power();

void vtx_set_protocol(uint8_t protocol);
void vtx_set_band(uint8_t band);
void vtx_set_freq(uint16_t freq);
void vtx_set_power(uint8_t power);