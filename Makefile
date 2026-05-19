ARMGNU = arm-none-eabi

COPS = -Wall -O2 -ffreestanding -nostdlib \
        -fno-exceptions \
        -fno-rtti \
        -fno-unwind-tables \
        -fno-asynchronous-unwind-tables \
        -std=c++11

ASMOPS = 

all: kernel7.img

kernel/font.o: kernel/font.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/font.cpp -o kernel/font.o

kernel/timer.o: kernel/timer.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/timer.cpp -o kernel/timer.o

kernel/graphics.o: kernel/graphics.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/graphics.cpp -o kernel/graphics.o

boot/start.o: boot/start.s
	$(ARMGNU)-as $(ASMOPS) boot/start.s -o boot/start.o

kernel/main.o: kernel/main.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/main.cpp -o kernel/main.o

kernel/uart.o: kernel/uart.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/uart.cpp -o kernel/uart.o

kernel/mailbox.o: kernel/mailbox.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/mailbox.cpp -o kernel/mailbox.o

kernel/framebuffer.o: kernel/framebuffer.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/framebuffer.cpp -o kernel/framebuffer.o

kernel/camera.o: kernel/camera.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/camera.cpp -o kernel/camera.o

kernel/memory.o: kernel/memory.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/memory.cpp -o kernel/memory.o

kernel/gpu_memory.o: kernel/gpu_memory.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/gpu_memory.cpp -o kernel/gpu_memory.o

kernel/dwc2.o: kernel/dwc2.cpp
	$(ARMGNU)-g++ $(COPS) -c kernel/dwc2.cpp -o kernel/dwc2.o

kernel7.img: linker.ld \
	boot/start.o \
	kernel/main.o \
	kernel/uart.o \
	kernel/mailbox.o \
	kernel/framebuffer.o \
	kernel/font.o \
	kernel/timer.o \
	kernel/graphics.o \
	kernel/memory.o \
	kernel/gpu_memory.o \
	kernel/dwc2.o \
	kernel/camera.o

	$(ARMGNU)-ld -T linker.ld -o kernel7.elf $^

	$(ARMGNU)-objcopy kernel7.elf -O binary kernel7.img

clean:
	rm -f boot/*.o
	rm -f kernel/*.o
	rm -f *.elf
	rm -f *.img