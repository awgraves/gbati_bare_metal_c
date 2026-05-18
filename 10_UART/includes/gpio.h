#ifndef GPIO_H_
#define GPIO_H_
#include "stm32f446xx.h"
#include <stdbool.h>

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

void button_init(void);
bool get_button_state(void);

#endif /* GPIO_H_ */
