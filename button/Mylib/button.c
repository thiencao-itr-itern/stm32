#include "button.h"

__weak void btn_release_callback(){
	
}
__weak void btn_press_short_callback(){  // nhan nha ra luon
	
}
__weak void btn_press_long_callback(){

}
__weak void btn_pressing_callback(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN){
//	switch(led_status)
//	{
//		case LED_OFF:
//				led_status = LED1_BLINK_1HZ;
//			break;
//		case LED1_BLINK_1HZ:
//				led_status = LED1_BLINK_5HZ;
//			break;
//		case LED1_BLINK_5HZ:
//				led_status = LED_OFF;
//			break;
//	}
}

void button_handle(Button_Typedef *button_x){
	uint8_t sta = HAL_GPIO_ReadPin(button_x->GPIOx, button_x->GPIO_Pin);
	if(sta != button_x->btn_filter){
		button_x->btn_filter = sta; // có su thay doi trang thai thi gan trang thai vao button filter
		button_x->is_debouncing = 1;
		button_x->time_debounce = HAL_GetTick();
	}
	// xu ly debounce
	if(button_x->is_debouncing == 1 && HAL_GetTick() - button_x->time_debounce >= 15){
		button_x->btn_current = button_x->btn_filter;
		button_x->is_debouncing = 0;
	}
	// xu li nhan nha
	if(button_x->btn_current != button_x->btn_last){
		if(button_x->btn_current == 0){ //Nhan xuong
			button_x->is_press_timeout = 1;
			btn_pressing_callback(button_x->GPIOx, button_x->GPIO_Pin);
			button_x->time_start_press = HAL_GetTick();
		}
		else {			// nha ra
			if (HAL_GetTick() - button_x->time_start_press	<= 1000){
					btn_press_short_callback();
			}
			btn_release_callback();
			button_x->is_press_timeout = 0;
		}
		button_x->btn_last = button_x->btn_current;
	}
	// ===== nhan giu ===========
	if(button_x->is_press_timeout && (HAL_GetTick() - button_x->time_start_press >= 3000))
	{
		btn_press_long_callback();
		button_x->is_press_timeout = 0;
	}
}
void button_init(Button_Typedef *button_x, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	button_x->GPIOx = GPIOx;
	button_x->GPIO_Pin = GPIO_Pin;
}

