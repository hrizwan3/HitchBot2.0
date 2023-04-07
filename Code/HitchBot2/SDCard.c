/*
 * SDCardComm.c
 *
 * Created: 4/6/2023 9:22:37 PM
 *  Author: hrizwan3
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"


#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define SPI_SS_PIN   PB2
#define SPI_MOSI_PIN PB3
#define SPI_MISO_PIN PB4
#define SPI_SCK_PIN  PB5

void spi_init(void) {
	// Set MOSI, SCK, and SS as outputs
	DDRB |= (1 << PINB3) | (1 << PINB5) | (1 << PINB2);

	// Set MISO as input
	DDRB &= ~(1 << PINB4);

	// Enable SPI, set as master, set clock rate fck/128
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

	// Set SS high
	PORTB |= (1 << PINB2);
}

uint8_t spi_transfer(uint8_t data) {
	// Load data into the SPI data register
	SPDR = data;

	// Wait until the transmission is complete
	while (!(SPSR & (1 << SPIF)));

	// Return the received data
	return SPDR;
}

uint8_t sd_send_command(uint8_t cmd, uint32_t arg) {
	uint8_t response, i;

	// Send the command
	spi_transfer(cmd | 0x40);
	spi_transfer(arg >> 24);
	spi_transfer(arg >> 16);
	spi_transfer(arg >> 8);
	spi_transfer(arg);

	// Send the correct CRC for CMD0, CMD8, or 0x01 for all other commands
	if (cmd == 0) {
		spi_transfer(0x95);
		} else if (cmd == 8) {
		spi_transfer(0x87);
		} else {
		spi_transfer(0x01);
	}

	// Wait for a valid response (0xFF is not valid)
	for (i = 0; i < 10; ++i) {
		response = spi_transfer(0xFF);
		if (response != 0xFF) {
			break;
		}
	}

	return response;
}

uint8_t sd_read_block(uint32_t block_address, uint8_t *buffer) {
	uint16_t i;

	// Send CMD17 to read a single block
	if (sd_send_command(17, block_address) != 0x00) {
		return 1; // Error: command not accepted
	}

	// Wait for the start of the data token (0xFE)
	while (spi_transfer(0xFF) != 0xFE);

	// Read 512 bytes of data
	for (i = 0; i < 512; ++i) {
		buffer[i] = spi_transfer(0xFF);
	}

	// Read and discard the CRC
	spi_transfer(0xFF);
	spi_transfer(0xFF);

	return 0;
}


uint8_t sd_write_block(uint32_t block_address, const uint8_t *buffer) {
	uint16_t i;

	// Send CMD24 to write a single block
	if (sd_send_command(24, block_address) != 0x00) {
		return 1; // Error: command not accepted
	}

	// Send the start of the data token (0xFE)
	spi_transfer(0xFE);

	// Write 512 bytes of data
	for (i = 0; i < 512; ++i) {
		spi_transfer(buffer[i]);
	}

	// Send a dummy CRC
	spi_transfer(0xFF);
	spi_transfer(0xFF);

	// Check for a valid response (0x05 is a valid response)
	if ((spi_transfer(0xFF) & 0x1F) != 0x05) {
		return 2; // Error: data not accepted
	}

	// Wait for the card to finish writing
	while (spi_transfer(0xFF) == 0x00);

	return 0;
}

uint8_t sd_init(void) {
	uint8_t i, response;
	uint32_t retry;

	// Send 80 clock cycles (10 bytes)
	for (i = 0; i < 10; ++i) {
		spi_transfer(0xFF);
	}

	// Send CMD0 to reset the card
	response = sd_send_command(0, 0);
	if (response != 0x01) {
		return 1; // Error: card did not enter idle state
	}

	// Send CMD8 to check the card's voltage range
	response = sd_send_command(8, 0x000001AA);
	if (response == 0x05) {
		return 2; // Error: card does not support the required voltage range
	}

	// Read the remaining bytes of the R7 response
	for (i = 0; i < 4; ++i) {
		response = spi_transfer(0xFF);
	}

	// Send ACMD41 repeatedly until the card exits the idle state (response is 0x00)
	retry = 0;
	do {
		// Send CMD55 (app command) first
		sd_send_command(55, 0);
		// Send ACMD41 with HCS (high capacity support) bit set
		response = sd_send_command(41, 0x40000000);
		retry++;
	} while (response != 0x00 && retry < 1000000);

	if (retry == 1000000) {
		return 3; // Error: card initialization timed out
	}

	// Check for high capacity (SDHC) cards
	response = sd_send_command(58, 0);
	if (response == 0x00) {
		response = spi_transfer(0xFF);
		if (response & 0x40) {
			// SDHC card
			} else {
			// Standard capacity card
		}
	}

	// Read the remaining bytes of the R3 response
	for (i = 0; i < 3; ++i) {
		response = spi_transfer(0xFF);
	}

	// De-select the card
	PORTB |= (1 << PINB2);
	spi_transfer(0xFF);

	return 0;
}

