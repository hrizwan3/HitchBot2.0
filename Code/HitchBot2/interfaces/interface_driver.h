
/*
 * interface_driver.h
 *
 * Created: 3/25/2023 4:14:38 PM
 *  Author: hunter stilp
 */ 

#ifndef INTERFACE_DRIVER_H
#define INTERFACE_DRIVER_H

#include "epd3in7.h"
#include "epdpaint.h"


typedef struct Interface {
	int mode; //0=displaying bmp file; 1=texting mode;
	Paint question1_text_box;
	Paint question2_text_box;
	Paint question3_text_box;
	Paint answer_text_box;
	Paint left_eye;
	Paint right_eye;
} Interface;

void init_interface(Interface* interface);
void update_question_boxes(char *question1, char *question2, char *question3);
void update_screen(void);
void draw_string_box(int xStart, int yStart, int width, int height, const char *string, bool borders);
void update_answer_box(char *answer);


#endif // INTERFACE_DRIVER_H