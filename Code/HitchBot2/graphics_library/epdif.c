/**
 *  @filename   :   epdif.c
 *  @brief      :   Implements EPD interface functions for ATmega328P
 *                  Users have to implement all the functions in epdif.c
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * (The copyright notice and permission notice remain unchanged.)
 */

#include "epdif.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdint.h>



// Initialize SPI for ATmega328P
static void spi_init() {

    DDRB |= (1 << CS_PIN) | (1 << RST_PIN) | (1 << DC_PIN);
    DDRD &= ~(1 << BUSY_PIN);
	
	
	// Set MOSI (PB3), SCK (PB5) and SS (PB2) as output
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2);

    // Enable SPI, set as master, clock polarity and phase = 0, and clock = F_CPU/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// Transfer a byte using SPI
// @param data: the data byte to be transferred
// @return: the received data byte
static uint8_t spi_transfer(uint8_t data) {
    SPDR = data; // Load the data byte into the SPI Data Register
    while (!(SPSR & (1 << SPIF))); // Wait for the transfer to complete
    return SPDR; // Return the received data byte
}

// Set the digital output value of a pin
// @param pin: the pin number
// @param value: the digital output value (HIGH or LOW)
void epd_digital_write(uint8_t pin, bool value) {
    if (value) {
        PORTB |= (1 << pin);
    } else {
        PORTB &= ~(1 << pin);
    }
}

// Read the digital input value of a pin
// @param pin: the pin number
// @return: the digital input value (HIGH or LOW)
bool epd_digital_read(uint8_t pin) {
    return (PIND & (1 << pin)) != 0;
}

// Pause the program execution for a specified number of milliseconds
// @param delaytime: the number of milliseconds to pause
void epd_delay_ms(unsigned int delaytime) {
    while (delaytime--) {
        _delay_ms(1);
    }
}

// Transfer data to the EPD via SPI
// @param data: the data byte to be transferred
void epd_spi_transfer(uint8_t data) {
    epd_digital_write(CS_PIN, false); // Set the Chip Select pin LOW to enable the SPI device
    spi_transfer(data); // Transfer the data byte via SPI
    epd_digital_write(CS_PIN, true); // Set the Chip Select pin HIGH to disable the SPI device
}

// Initialize the interface for the EPD
// @return: 0 if successful, non-zero if there is an error
int epd_if_init(void) {
//    //Set the Chip Select, Reset, and Data/Command pins as output
//        DDRB |= (1 << CS_PIN) | (1 << RST_PIN) | (1 << DC_PIN);
//    
//        // Set the Busy pin as input
//        DDRB &= ~(1 << BUSY_PIN);
//^^DONT THINK THATS NECESARY. ITS ALL IN SPI_INIT

    spi_init(); // Initialize SPI

    return 0; // Return 0 to indicate successful initialization
}

//END FILE