#include "epd3in7.h"
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
char String[25];

#include "epdpaint.h"
#include "interface_driver.h"



int main(void) {
	



// 	while(1){
// 		
// 	}
	

	
	Interface interface;

	
	init_interface(&interface);
	
	char str1[] = "So where are you trying to go";
	char str2[] = "How long have you been in austin for";
	char str3[] = "Nah i am not helping you. This doesn't make sense";
	char stra[] = "A: update answer box. I need this line to overflow";
	
	
	
	update_question_boxes(str1, str2, str3);
	update_answer_box(stra);//Nah Fuck you lil bitch. Take me to austin");

	update_question_boxes(str3, str1, str2);
	
	epd_sleep();
	
	
	
	
	
	
	_delay_ms(99999);
	
	//
	// 	UART_init(9600);
	//
	// 	sprintf(String,"Hello world! \n");
	// 	UART_putstring(String);
	//
	// 	epd_init();
	// 	epd_clear(1);
	// 	//epd_display_frame(IMAGE_DATA, true);
	// 	epd_display_frame_part(IMAGE_DATA, 0,0,280,480, false);
	//
	// 	_delay_ms(2000);
	//
	// 	epd_turn_on_display();
	//
	//
	//
	//
	// 	_delay_ms(3000);
	//
	// 	epd_clear(1);
	//
	// 	_delay_ms(99999);
	//
	// 	//epd_display_frame_part(IMAGE, 50,3,50,3, false);
	//
	// 	_delay_ms(3000);
	//
	// 	epd_turn_on_display();
	//
	// 	_delay_ms(2000);
	//
	// 	epd_sleep();
	while(1){
		
	}
	return 0;
}