#include <stdint.h>

typedef struct {
  volatile uint32_t MODER;    // offset 0x00
  volatile uint32_t OTYPER;   // offset 0x04
  volatile uint32_t OSPEEDER; // offset 0x08
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
} GPIO_TypeDef;

typedef struct {
  volatile uint32_t DUMMY[12]; // unused parts for now: 4 bytes x 12 = 48
  volatile uint32_t AHB1ENR;   // offset 0x30
} RCC_TypeDef;

#define RCC_BASE 0x40023800
#define GPIOA_BASE 0x40020000

#define RCC ((RCC_TypeDef *)RCC_BASE)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

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

    for (int i = 0; i < 5000000; i++) {
      // do nothing
    }
  }
}
