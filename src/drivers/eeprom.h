#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <stddef.h>

// Init
void eeprom_init(void);

// Single byte
uint8_t eeprom_read_byte(uint16_t addr);
void    eeprom_write_byte(uint16_t addr, uint8_t data);

// Multi-byte
void eeprom_read(uint16_t addr, void *buf, size_t len);
void eeprom_write(uint16_t addr, const void *buf, size_t len);

#endif