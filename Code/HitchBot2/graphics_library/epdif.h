/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.c providing EPD interface functions
 *                  Users have to implement all the functions in epdif.c
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * (The copyright notice and permission notice remain unchanged.)
 */

#ifndef EPDIF_H
#define EPDIF_H

#include <stdbool.h>
#include <stdint.h>

// Pin definition
#define RST_PIN         PB0 // Change to the appropriate pin number for ATmega328P
#define DC_PIN          PB1 // Change to the appropriate pin number for ATmega328P
#define CS_PIN          PB2 // Change to the appropriate pin number for ATmega328P
#define BUSY_PIN        PD7 // Change to the appropriate pin number for ATmega328P

// Function prototypes
int epd_if_init(void);
void epd_digital_write(uint8_t pin, bool value);
bool epd_digital_read(uint8_t pin);
void epd_delay_ms(unsigned int delaytime);
void epd_spi_transfer(uint8_t data);

#endif