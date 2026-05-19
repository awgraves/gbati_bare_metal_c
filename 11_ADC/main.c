#include "adc.h"
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

int sensor_value;

int main(void) {
  uart_init();
  tim2_1hz_init();

  pa1_adc_init();
  start_conversion();

  printf("Hello from STM%d!\r\n", 32);

  while (1) {
    sensor_value = adc_read();

    printf("Sensor value: %d\r\n", sensor_value);

    delay_s(1);
  }
}
