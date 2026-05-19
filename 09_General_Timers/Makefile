CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 \
				 -I CMSIS/Include \
				 -I CMSIS/Device/ST/STM32F4xx/Include \
				 -I includes
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=code.map

final : code.elf

compile_commands :
	bear -- make -B

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

stm32f446_startup.o : stm32f446_startup.c
	$(CC) $(CFLAGS) $^ -o $@

gpio.o : gpio.c
	$(CC) $(CFLAGS) $^ -o $@

systick.o : systick.c
	$(CC) $(CFLAGS) $^ -o $@

tim.o : tim.c
	$(CC) $(CFLAGS) $^ -o $@

code.elf : main.o stm32f446_startup.o gpio.o systick.o tim.o
	$(CC) $(LDFLAGS) *.o -o $@

.PHONY: load flash clean

load:
	openocd -f board/st_nucleo_f4.cfg

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program code.elf verify reset exit"

clean:
	rm -rf *.o *.elf *.map

