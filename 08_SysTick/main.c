#include "gpio.h"
#include "systick.h"

int main(void) {
  led_init();

  while (1) {
    systick_msec_delay(5000);
    led_toggle();
  }
}
