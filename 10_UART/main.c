#include "tim.h"
#include "uart.h"
#include <stdint.h>

void delay_s(uint32_t s) {
  while (s > 0) {
    while (!(TIM2->SR & SR_UIF))
      ;

    // clear UIF
    TIM2->SR &= ~SR_UIF;
    s--;
  }
}

int main(void) {
  uart_init();
  tim2_1hz_init();

  uart_print("Hello from STM32! Type something and see an echo:\r\n");

  while (1) {
    uart_echo();
  }
}
