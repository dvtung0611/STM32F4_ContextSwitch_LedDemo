CC = arm-none-eabi-gcc
MCU_ARCHITECTURE = cortex-m4
CFLAGS = -mthumb -mcpu=$(MCU_ARCHITECTURE) -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS = -mthumb -mcpu=$(MCU_ARCHITECTURE) --specs=nano.specs -mfloat-abi=soft -T linker_stm32f407vgtx.ld -Wl,-Map=final.map
# LDFLAGS_SEMI = -mthumb -mcpu=$(MCU_ARCHITECTURE) --specs=rdimon.specs -mfloat-abi=soft -T linker_stm32f407vgtx.ld -Wl,-Map=final.map

.PHONY: all clean

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
all: $(OBJ) final.elf

semi: $(OBJ) final_semi.elf

clean:
	rm -f *.i *.s *.o *.elf *.map

load:
	openocd -f board/stm32f4discovery.cfg

#Rule compile
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

final.elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

final_semi.elf: main.o led.o startup_stm32f407vgtx.o
	$(CC) $(LDFLAGS_SEMI) $^ -o $@