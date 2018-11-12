#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//输出一个整数的每一位
void  print_int_bits(unsigned int value)
{
	unsigned int flag = 0x80000000;
	while (flag)
	{
		printf("%d ", (value&flag) / flag);
		flag >>= 1;
	}
}

int main()
{
	int a = 1234;
	print_int_bits(a);
	return 0;
}