#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

unsigned int  reverse_bit(unsigned int value)
{
	value = (value & 0x55555555) << 1 | (value & 0xAAAAAAAA) >> 1;
	value = (value & 0x33333333) << 2 | (value & 0xCCCCCCCC) >> 2;
	value = (value & 0x0F0F0F0F) << 4 | (value & 0x0F0F0F0F) >> 4;
	value = (value & 0x00FF00FF) << 8 | (value & 0XFF00FF00) >> 8;
	value = (value & 0x0000FFFF) << 16 | (value & 0xFFFF0000) >> 16;
	return value;

}

int main()
{
	int x = 15;
	printf("%x\n", x);
	x = reverse_bit(x);
	printf("二进制左右翻转后:\nx = %x", x);
	return 0;
}