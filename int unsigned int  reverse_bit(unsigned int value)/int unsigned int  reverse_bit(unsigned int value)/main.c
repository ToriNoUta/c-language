#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

unsigned char reverse_bit_char(unsigned char y)
{
	int i = 0;
	unsigned char blank = 0x01;
	unsigned char num = 0;
	for (i = 7; i >0; i -= 2)
	{
		num = (y >> i)&(blank) | num;
		blank <<= 1;
	}
	blank = 0x80;
	for (i = 7; i >0; i -= 2)
	{
		num = (y << i)&(blank) | num;
		blank >>= 1;
	}
	return num;
}

unsigned int reverse_bit(unsigned int x)
{
	unsigned short a = x / 0x10000;
	unsigned short b = x;
	unsigned char c = b / 0x100;
	unsigned char d = b;
	c = reverse_bit_char(c);
	d = reverse_bit_char(d);
	c = c^d;
	d = c^d;
	c = c^d;
	b = c * 0x100 + d;
	a = a^b;
	b = a^b;
	a = a^b;
	x = a * 0x10000 + b;
	return x;
}

int main()
{
	unsigned int x = 15;
	printf("x = %x", x);
	x = reverse_bit(x);
	printf("×ªÖÃºó£ºx = %x", x);

	return 0;
}