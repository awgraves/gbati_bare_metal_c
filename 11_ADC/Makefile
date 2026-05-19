CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 \
				 -I CMSIS/Include \
				 -I CMSIS/Device/ST/STM32F4xx/Include \
				 -I includes \
				 -g
LDFLAGS = -mcpu=cortex-m4 \
					-mthumb \
					-nostartfiles \
					--specs=nano.specs \
					--specs=nosys.specs \
					-T stm32_ls.ld -Wl,-Map=code.map

final : code.elf

compile_commands :
	bear -- make -B

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

stm32f446_startup.o : stm32f446_startup.c
	$(CC) $(CFLAGS) $^ -o $@

tim.o : tim.c
	$(CC) $(CFLAGS) $^ -o $@

uart.o : uart.c
	$(CC) $(CFLAGS) $^ -o $@

adc.o : adc.c
	$(CC) $(CFLAGS) $^ -o $@

code.elf : main.o stm32f446_startup.o uart.o tim.o adc.o
	$(CC) $(LDFLAGS) *.o -o $@

.PHONY: load flash clean

load:
	openocd -f board/st_nucleo_f4.cfg

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program code.elf verify reset exit"

clean:
	rm -rf *.o *.elf *.map

