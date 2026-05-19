#include "gpio.h"

#define GPIOAEN (1U << 0)
#define GPIOCEN (1U << 2)

#define BTN_PIN (1U << 13)

#define LED_PIN (1U << 5)
#define LED_BS5 (1U << 5)        // bit set pin 5
#define LED_BR5 (1U << (5 + 16)) // bit reset pin 5

void led_init(void) {
  // enable clock
  RCC->AHB1ENR |= GPIOAEN;
  // set pa5 mode to output
  GPIOA->MODER |= (1U << 10);
  GPIOA->MODER &= ~(1U << 11);
}

void led_on(void) { GPIOA->BSRR = LED_BS5; }

void led_off(void) { GPIOA->BSRR = LED_BR5; }

void led_toggle(void) { GPIOA->ODR ^= LED_PIN; }

void button_init(void) {
  // enable clock
  RCC->AHB1ENR |= GPIOCEN;

  // set PC13 as output
  GPIOC->MODER &= ~((1U << 26) | (1U << 27));
}

bool get_button_state(void) {
  // Note button is active low

  return !(GPIOC->IDR & BTN_PIN);
}
