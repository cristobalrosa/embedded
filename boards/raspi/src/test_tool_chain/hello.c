//  Compile: arm-linux-gnueabihf-gcc hello.c -o hello
//  Test with qemu
//  qemu-arm -L ~/bin/raspitools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc ./hello

#include <stdio.h>
int main()
{
    printf("Testing the raspi toolchain\n");
}
