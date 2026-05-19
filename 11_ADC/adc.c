#include "adc.h"
#include <stdint.h>

#define GPIOAEN (1U << 0)
#define ADC1EN (1U << 8)
#define ADC_CH1 (1U << 0)
#define ADC_SEQ_LEN_1 0x00

#define CR2_ADCON (1U << 0)
#define CR2_CONT (1U << 1)
#define CR2_SWSTART (1U << 30)
#define SR_EOC (1U << 1)

void pa1_adc_init(void) {
  // enable clock for ADC GPIO
  RCC->AHB1ENR |= GPIOAEN;

  // Set PA 1 to analog mode
  GPIOA->MODER |= (3U << (2 * 1));

  // enable adc module
  RCC->APB2ENR |= ADC1EN;

  ADC1->SQR3 = ADC_CH1;

  ADC1->SQR1 = ADC_SEQ_LEN_1;

  ADC1->CR2 |= CR2_ADCON;
}

void start_conversion(void) {
  // enable continuous conversion
  ADC1->CR2 |= CR2_CONT;

  // start ADC conversion
  ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void) {
  // wait for conversion complete
  while (!(ADC1->SR & SR_EOC))
    ;

  return ADC1->DR;
}
