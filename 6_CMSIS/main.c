#include "stm32f446xx.h"
#include <stdint.h>

#define GPIOAEN (1U << 0)
#define PIN5 (1U << 5)

#define LED_PIN PIN5

int main(void) {
  // clock enable for the bus where PA5 lives
  RCC->AHB1ENR |= GPIOAEN;

  // set pins 10 and 11 to 1 and 0 respectively
  // this indicates general output mode for PA5
  GPIOA->MODER |= (1U << 10);
  GPIOA->MODER &= ~(1U << 11);

  while (1) {
    // set PA5 HIGH
    GPIOA->ODR ^= LED_PIN;

    for (int i = 0; i < 100000; i++) {
      // do nothing
    }
  }
}
