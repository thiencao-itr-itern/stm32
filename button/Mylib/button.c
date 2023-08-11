#include "button.h"
uint8_t btn_current = 1;
uint8_t btn_last = 1;
uint8_t btn_filter = 1;
uint8_t is_debouncing;
uint32_t time_debounce;
uint32_t time_start_press;
uint8_t is_press_timeout;
__weak void btn_release_callback(){
	
}
__weak void btn_press_short_callback(){  // nhan nha ra luon
	
}
__weak void btn_press_long_callback(){

}
__weak void btn_pressing_callback(){
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

void button_handle(){
	uint8_t sta = HAL_GPIO_ReadPin(button_GPIO_Port, button_Pin);
	if(sta != btn_filter){
		btn_filter = sta; // có su thay doi trang thai thi gan trang thai vao button filter
		is_debouncing = 1;
		time_debounce = HAL_GetTick();
	}
	// xu ly debounce
	if(is_debouncing == 1 && HAL_GetTick() - time_debounce >= 15){
		btn_current = btn_filter;
		is_debouncing = 0;
	}
	// xu li nhan nha
	if(btn_current != btn_last){
		if(btn_current == 0){ //Nhan xuong
			is_press_timeout = 1;
			btn_pressing_callback();
			time_start_press = HAL_GetTick();
		}
		else {			// nha ra
			if (HAL_GetTick() - time_start_press	<= 1000){
					btn_press_short_callback();
			}
			btn_release_callback();
			is_press_timeout = 0;
		}
		btn_last = btn_current;
	}
	// ===== nhan giu ===========
	if(is_press_timeout && (HAL_GetTick() - time_start_press >= 3000))
	{
		btn_press_long_callback();
		is_press_timeout = 0;
	}
}

