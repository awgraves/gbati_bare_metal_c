#include "uart.h"
#include <stdint.h>

#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define DBG_UART_BAUDRATE 115200
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define CR1_TE (1U << 3)
#define CR1_RE (1U << 2)
#define CR1_UE (1U << 13)
#define SR_TXE (1U << 7)
#define SR_RXNE (1U << 5)

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch) {
  uart_write(ch);
  return ch;
}

int _write(int fd, char *ptr, int len) {
  while (*ptr)
    __io_putchar(*ptr++);

  return len;
}

void uart_init(void) {
  // enable clock access to GPIOA
  RCC->AHB1ENR |= GPIOAEN;

  // set mode of PA2 to alternate function mode
  GPIOA->MODER &= ~(1U << 4);
  GPIOA->MODER |= (1U << 5);

  // set mode of PA3 to alt function mode
  GPIOA->MODER |= (0x2 << (2 * 3));

  // set alt func type AF7 PA2 (UART2_TX)
  GPIOA->AFR[0] |= (1U << 8);
  GPIOA->AFR[0] |= (1U << 9);
  GPIOA->AFR[0] |= (1U << 10);
  GPIOA->AFR[0] &= ~(1U << 11);

  // and again for UART2_RX PA3 (AF7)
  GPIOA->AFR[0] &= ~(0xF << (4 * 3)); // clear it
  GPIOA->AFR[0] |= (0x7 << (4 * 3));  // set

  // enable clock access to UART2EN
  RCC->APB1ENR |= UART2EN;

  // configure baudrate
  uart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);

  // enable transfer and receive
  USART2->CR1 = CR1_TE | CR1_RE;

  // enable uart module
  USART2->CR1 |= CR1_UE;
}

void uart_print(const char *s) {
  while (*s)
    __io_putchar(*s++);
}

#define BUFF_SIZE 50
static char buffer[BUFF_SIZE];
static uint32_t buff_idx = 0;

void flush_buffer(void) {
  uart_print("Echo: ");
  for (int i = 0; i < buff_idx; i++) {
    uart_write(buffer[i]);
  }
  uart_print("\r\n");
  buff_idx = 0;
}

void uart_echo(void) {

  while ((USART2->SR & SR_RXNE) && buff_idx < BUFF_SIZE) {
    volatile char c = USART2->DR;

    if (c == '\r') {
      flush_buffer();
      break;
    } else {
      buffer[buff_idx++] = c;
    }
  }

  if (buff_idx >= BUFF_SIZE)
    flush_buffer();
}

static void uart_write(int ch) {
  // make sure transmit data register is empty
  while (!(USART2->SR & SR_TXE))
    ;

  // write to transmit data register
  USART2->DR = (ch & 0xFF);
}

static uint16_t compute_uart_baud(uint32_t periph_clk, uint32_t baudrate) {
  return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate) {
  USART2->BRR = compute_uart_baud(periph_clk, baudrate);
}
