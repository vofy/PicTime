#include "eeprom.h"
#include <xc.h>
#include <stdint.h>


static uint8_t spi_transfer(uint8_t data)
{
    SPI2BUF = data;
    while (!SPI2STATbits.SPIRBF);
    return SPI2BUF;
}

static uint8_t eeprom_read_status(void)
{
    uint8_t status;

    CS_LOW();
    spi_transfer(CMD_RDSR);
    status = spi_transfer(0xFF);
    CS_HIGH();

    return status;
}

static void eeprom_wait_ready(void)
{
    while (eeprom_read_status() & STATUS_WIP);
}

void eeprom_init(void)
{
    // CS pin
    EEPROM_CS_TRIS = 0;
    CS_HIGH();

    // SPI2 pins
    TRISGbits.TRISG6 = 0; // SCK2
    TRISGbits.TRISG7 = 1; // SDI2
    TRISGbits.TRISG8 = 0; // SDO2

    SPI2STATbits.SPIEN = 0;

    SPI2CON1 = 0;
    SPI2CON1bits.MSTEN = 1;

    SPI2CON1bits.CKP = 0;
    SPI2CON1bits.CKE = 1;

    SPI2CON1bits.SMP = 0;
    SPI2CON1bits.MODE16 = 0;

    SPI2CON1bits.PPRE = 0b10;
    SPI2CON1bits.SPRE = 0b110;

    SPI2STATbits.SPIROV = 0;
    SPI2STATbits.SPIEN = 1;
}

uint8_t eeprom_read_byte(uint16_t addr)
{
    uint8_t data;

    eeprom_wait_ready();

    CS_LOW();
    spi_transfer(CMD_READ);
    spi_transfer(addr >> 8);
    spi_transfer(addr & 0xFF);
    data = spi_transfer(0xFF);
    CS_HIGH();

    return data;
}

void eeprom_write_byte(uint16_t addr, uint8_t data)
{
    eeprom_wait_ready();

    // Write enable
    CS_LOW();
    spi_transfer(CMD_WREN);
    CS_HIGH();

    __delay_us(1);

    // Write
    CS_LOW();
    spi_transfer(CMD_WRITE);
    spi_transfer(addr >> 8);
    spi_transfer(addr & 0xFF);
    spi_transfer(data);
    CS_HIGH();
}

void eeprom_read(uint16_t addr, void *buf, size_t len)
{
    uint8_t *p = buf;

    eeprom_wait_ready();

    CS_LOW();
    spi_transfer(CMD_READ);
    spi_transfer(addr >> 8);
    spi_transfer(addr & 0xFF);

    while (len--)
        *p++ = spi_transfer(0xFF);

    CS_HIGH();
}

void eeprom_write(uint16_t addr, const void *buf, size_t len)
{
    const uint8_t *p = buf;

    while (len > 0)
    {
        uint8_t page_offset = addr & 0x3F;
        uint8_t chunk = 64 - page_offset;

        if (chunk > len)
            chunk = len;

        eeprom_wait_ready();

        // Write enable
        CS_LOW();
        spi_transfer(CMD_WREN);
        CS_HIGH();

        __delay_us(1);

        // Write page
        CS_LOW();
        spi_transfer(CMD_WRITE);
        spi_transfer(addr >> 8);
        spi_transfer(addr & 0xFF);

        for (uint8_t i = 0; i < chunk; i++)
            spi_transfer(p[i]);

        CS_HIGH();

        addr += chunk;
        p += chunk;
        len -= chunk;
    }
}