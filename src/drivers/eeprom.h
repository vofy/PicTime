#ifndef EEPROM_H
#define EEPROM_H

#include "system.h"
#include <xc.h>

#include <stdint.h>
#include <stddef.h>

// Chip select definitions
#define EEPROM_CS_LAT  LATDbits.LATD12
#define EEPROM_CS_TRIS TRISDbits.TRISD12

#define CS_LOW()   (EEPROM_CS_LAT = 0)
#define CS_HIGH()  (EEPROM_CS_LAT = 1)

// Chip select commands definition
#define CMD_WREN  0x06
#define CMD_RDSR  0x05
#define CMD_WRITE 0x02
#define CMD_READ  0x03

#define STATUS_WIP 0x01

// Init
void eeprom_init(void);

// Single byte
uint8_t eeprom_read_byte(uint16_t addr);
void    eeprom_write_byte(uint16_t addr, uint8_t data);

// Multi-byte
void eeprom_read(uint16_t addr, void *buf, size_t len);
void eeprom_write(uint16_t addr, const void *buf, size_t len);

#endif