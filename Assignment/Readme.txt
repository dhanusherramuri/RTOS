sudo apt update

sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi gdb-multiarch build-essential

arm-none-eabi-gcc --version


sudo apt-get install vim


mkdir sandbox
cd sandbox
mkdir 001_add_prog
cd 001_add_prog

cat add_prog.c 
int main(void)
{
	int a = 10, b = 20;
	int c = a + b;
}


arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -g  -c add_prog.c -o add_prog.o

arm-none-eabi-objdump  -S add_prog.o





mkdir 001_add_prog
cd 001_add_prog
cat add_prog.c 
int main(void)
{
	int a = 10, b = 20;
	int c = a + b;
	return 0;
}


arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -g -c add_prog.c -o add_prog.o
arm-none-eabi-objdump -S add_prog.o
arm-none-eabi-as -mcpu=cortex-m3 -mthumb startup_stm32f103.s -o startup.o
arm-none-eabi-ld -T STM32F103C8.ld add_prog.o startup.o -o firmware.elf
arm-none-eabi-readelf -a  firmware.elf
arm-none-eabi-objdump -S firmware.elf











