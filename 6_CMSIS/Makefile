CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 \
				 -I CMSIS/Include \
				 -I CMSIS/Device/ST/STM32F4xx/Include
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=code.map

final : code.elf

compile_commands :
	bear -- make -B

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

stm32f446_startup.o : stm32f446_startup.c
	$(CC) $(CFLAGS) $^ -o $@

code.elf : main.o stm32f446_startup.o
	$(CC) $(LDFLAGS) *.o -o $@

load:
	openocd -f board/st_nucleo_f4.cfg

clean:
	rm -rf *.o *.elf *.map

