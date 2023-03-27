

#include <avr/io.h>
#include <util/delay.h>

#include "interface_driver.h"
#include <string.h>
#include <stdlib.h>


void init_interface(Interface* interface) {
	epd_init();
	epd_clear(1);
	_delay_ms(1000);
	
// 	//generic empty image
// 	unsigned char empty_image[1];
// 	
// 	//generic question text box info
// 	int question_width = 40;      // Width of the display
// 	int question_height = 120;      // Height of the display
// 
// 	
// 	//question1 text box init
// 	Paint question1_text_box;
// 	Paint_Init(&question1_text_box, empty_image, question_width, question_height);
// 	Paint_SetRotate(&question1_text_box, ROTATE_270);
// 	interface->question1_text_box = question1_text_box;
// 	
// 	//question2 text box init
// 	Paint question2_text_box;
// 	Paint_Init(&question2_text_box, empty_image, question_width, question_height);
// 	Paint_SetRotate(&question2_text_box, ROTATE_270);
// 	interface->question2_text_box = question2_text_box;
// 	
// 	//question3 text box init
// 	Paint question3_text_box;
// 	Paint_Init(&question3_text_box, empty_image, question_width, question_height);
// 	Paint_SetRotate(&question3_text_box, ROTATE_270);
// 	interface->question3_text_box = question3_text_box;
// 	
// 	
// 	//answer box init
// 	int answer_width = 40;      // Width of the display
// 	int answer_height = 120;      // Height of the display
// 	
// 	Paint answer_text_box;
// 	Paint_Init(&answer_text_box, empty_image, answer_width, answer_height);
// 	Paint_SetRotate(&answer_text_box, ROTATE_270);
// 	interface->answer_text_box = answer_text_box;
// 	
// 	
// 	//generic eye paint info
// 	int eye_width = 40;      // Width of the display
// 	int eye_height = 120;      // Height of the display
// 	
// 	//right eye paint init
// 	Paint right_eye;
// 	Paint_Init(&right_eye, empty_image, eye_width, eye_height);
// 	Paint_SetRotate(&right_eye, ROTATE_270);
// 	interface->right_eye = right_eye;
// 	
// 	//left eye paint init
// 	Paint left_eye;
// 	Paint_Init(&left_eye, empty_image, eye_width, eye_height);
// 	Paint_SetRotate(&left_eye, ROTATE_270);
// 	interface->left_eye = left_eye;
}


void update_question_boxes(char *question1, char *question2, char *question3)
{
	draw_string_box(200,0,80,160, question3, true);
	draw_string_box(200,160,80,160, question2, true);
	draw_string_box(200,320,80,160, question1, true);
}

void update_answer_box(char *answer)
{
	draw_string_box(144, 216, 32, 256, answer, false);
}

void draw_string_box(int xStart, int yStart, int width, int height, const char *string, bool borders){
	//string = "this is some bs. Why TF IS IT NOT WORKING";
	int space_between_lines = 15;
	
	int image_size = width / 8 * height ;  // Calculate the size of the image buffer
	
	//init paint
	Paint paint;
	unsigned char image[image_size];
// 	unsigned char *image = (unsigned char *) malloc(image_size * sizeof(unsigned char)); // Allocate memory dynamically
// 	if (image == NULL) {
// 		draw_string_box(8, 8, 72, 72, "not enough mem", true);
// 	}
	Paint_Init(&paint, image, width, height);
	Paint_SetRotate(&paint, ROTATE_270);
	Paint_Clear(&paint, 1);
	
	//draw border
	if (borders) {
		Paint_DrawHorizontalLine(&paint, 0, 0, height, 0);
		Paint_DrawHorizontalLine(&paint, 0, width-1, height, 0);
		Paint_DrawVerticalLine(&paint, 1, 0, width, 0);
		Paint_DrawVerticalLine(&paint, height-1, 0, width, 0);
	}
	
	
	
	int max_chars_per_line = height / 9;
	int current_line = 0;
	size_t string_length = strlen(string);
	size_t start_pos = 0;

	while (start_pos < string_length) {
		int chars_to_copy = max_chars_per_line;
		if (start_pos + chars_to_copy < string_length) {
			while (string[start_pos + chars_to_copy] != ' ' && chars_to_copy > 0) {
				chars_to_copy--;
			}
			if (chars_to_copy == 0) {
				chars_to_copy = max_chars_per_line;
			}
		} else {
			chars_to_copy = string_length - start_pos;
		}

		char subset_individual_line[max_chars_per_line + 1];
		strncpy(subset_individual_line, string + start_pos, chars_to_copy);
		subset_individual_line[chars_to_copy] = '\0';
		
		

		int xPos = 0;
		int yPos = current_line * space_between_lines;
		Paint_DrawStringAt(&paint, xPos, yPos, subset_individual_line, &Font16, 0);

		start_pos += chars_to_copy;
		if (string[start_pos] == ' ') {
			start_pos++; // Skip the space character
		}
		current_line++;
	}
	
	
	epd_display_frame_part(Paint_GetImage(&paint), xStart, yStart, xStart+width, yStart+height, false);
	
	epd_turn_on_display();
	
	epd_display_frame_part(Paint_GetImage(&paint), xStart, yStart, xStart+width, yStart+height, false);
	
//	free(image);
}



void update_screen(void)
{
	epd_turn_on_display();
}