#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//扫描一个无符号整型数的二进制返回其中‘1’的个数
int count_one_bits(unsigned int value)
{
	int count = 0;
	unsigned int flag = 0x80000000;
	int i = 0;
	for (i = 0; i < 32; i++)
	{	
		if ((value&flag )== flag)count++;
		flag >>= 1;
	}
	return count;
}

int main()
{
	int c = 15;
	printf("c的二进制中‘1’的个数为：%d", count_one_bits(c));
	return 0;
}