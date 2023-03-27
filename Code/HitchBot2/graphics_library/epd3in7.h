/**
 *  @filename   :   epd3in7.h
 *  @brief      :   Header file for e-paper library epd3in7.c
 *  @author     :   Waveshare
 */
#ifndef EPD3IN7_H
#define EPD3IN7_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       280
#define EPD_HEIGHT      480

#define UWORD   unsigned int
#define UBYTE   unsigned char
#define UDOUBLE unsigned long

// Pin definition
// #define RST_PIN         PD6 // Change to the appropriate pin number for ATmega328P
// #define DC_PIN          PB1 // Change to the appropriate pin number for ATmega328P
// #define CS_PIN          PB0 // Change to the appropriate pin number for ATmega328P
// #define BUSY_PIN        PD7 // Change to the appropriate pin number for ATmega328P

int epd_init(void);
void epd_send_command(unsigned char command);
void epd_send_data(unsigned char data);
void epd_wait_until_idle(void);
void epd_reset(void);
void epd_display_frame(const UBYTE *Image, bool isBase);
void epd_display_frame_partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD iwidth, UWORD iheight);
void epd_display_frame_part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, bool isGC);
void epd_turn_on_display(void);
void epd_sleep(void);
void epd_clear(UBYTE mode);
void epd_load_lut(unsigned char mode);

#endif /* EPD3IN7_H */