#include "eeprom.h"
#include <xc.h>

// ==========================
// CONFIG ? VERIFY THIS
// ==========================

// SPI2 (adjust if needed)
#define SPIBUF      SPI2BUF
#define SPISTATbits SPI2STATbits
#define SPICON1     SPI2CON1
#define SPICON1bits SPI2CON1bits

// Moved from RB15 to RB14 to resolve conflict with LCD_RS
#define EEPROM_CS_LAT  LATBbits.LATB14
#define EEPROM_CS_TRIS TRISBbits.TRISB14

#define CS_LOW()   (EEPROM_CS_LAT = 0)
#define CS_HIGH()  (EEPROM_CS_LAT = 1)

// ==========================
// COMMANDS
// ==========================

#define CMD_WREN  0x06
#define CMD_RDSR  0x05
#define CMD_WRITE 0x02
#define CMD_READ  0x03

#define STATUS_WIP 0x01

// ==========================
// SPI (SAFE)
// ==========================

static uint8_t spi_transfer(uint8_t data)
{
    uint32_t timeout = 100000;

    SPIBUF = data;

    while (!SPISTATbits.SPIRBF)
    {
        if (--timeout == 0)
            return 0xFF; // fail-safe
    }

    return SPIBUF;
}

// ==========================
// EEPROM STATUS
// ==========================

static uint8_t eeprom_ready(void)
{
    uint8_t status;

    CS_LOW();
    spi_transfer(CMD_RDSR);
    status = spi_transfer(0xFF);
    CS_HIGH();

    return !(status & STATUS_WIP);
}

static void eeprom_wait_ready(void)
{
    while (!eeprom_ready());
}

// ==========================
// INIT
// ==========================

void eeprom_init(void)
{
    // CS pin
    EEPROM_CS_TRIS = 0;
    CS_HIGH();

    // SPI config (Mode 0)
    SPICON1 = 0;
    SPICON1bits.MSTEN = 1;
    SPICON1bits.CKP = 0;
    SPICON1bits.CKE = 1;
    SPICON1bits.SMP = 0;

    // Clock: Fcy / 16 (safe)
    SPICON1bits.PPRE = 0b10;
    SPICON1bits.SPRE = 0b110;

    SPISTATbits.SPIEN = 1;
}

// ==========================
// BYTE ACCESS
// ==========================

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

    // WREN
    CS_LOW();
    spi_transfer(CMD_WREN);
    CS_HIGH();

    // WRITE
    CS_LOW();
    spi_transfer(CMD_WRITE);
    spi_transfer(addr >> 8);
    spi_transfer(addr & 0xFF);
    spi_transfer(data);
    CS_HIGH();
}

// ==========================
// MULTI-BYTE
// ==========================

void eeprom_read(uint16_t addr, void *buf, size_t len)
{
    uint8_t *p = (uint8_t *)buf;

    eeprom_wait_ready();

    CS_LOW();
    spi_transfer(CMD_READ);
    spi_transfer(addr >> 8);
    spi_transfer(addr & 0xFF);

    for (size_t i = 0; i < len; i++)
        p[i] = spi_transfer(0xFF);

    CS_HIGH();
}

void eeprom_write(uint16_t addr, const void *buf, size_t len)
{
    const uint8_t *p = (const uint8_t *)buf;

    while (len > 0)
    {
        uint8_t page_offset = addr % 64;
        uint8_t chunk = 64 - page_offset;

        if (chunk > len)
            chunk = len;

        eeprom_wait_ready();

        // WREN
        CS_LOW();
        spi_transfer(CMD_WREN);
        CS_HIGH();

        // WRITE PAGE
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