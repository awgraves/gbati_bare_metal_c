#include "tim.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

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

  printf("Hello from STM%d! Type something and see an echo:\r\n", 32);

  while (1) {
    uart_echo();
  }
}
