#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"

typedef struct{
	uint8_t btn_current;
	uint8_t btn_last;
	uint8_t btn_filter;
	uint8_t is_debouncing;
	uint32_t time_debounce;
	uint32_t time_start_press;
	uint8_t is_press_timeout;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typedef;

//void btn_release_callback();
//void btn_press_short_callback();
//void btn_pressing_callback();
//void btn_press_long_callback();
void button_handle(Button_Typedef *button_x);
void button_init(Button_Typedef *button_x, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif


