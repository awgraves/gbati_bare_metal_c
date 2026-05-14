#include "gpio.h"
#include <stdint.h>

bool button_state;

int main(void) {
  led_init();
  button_init();

  while (1) {
    button_state = get_button_state();

    if (button_state) {
      led_on();
    } else {
      led_off();
    }
  }
}
