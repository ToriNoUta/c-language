#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//按偶数位和奇数位输出一个数的二进制序列
void print_int_bits_odd_even(unsigned int value)
{
	unsigned int flag = 0x80000000;
	printf("该整形数中的偶数位序列为：\n");
	while(flag)
	{
		printf("%d ", (flag&value)/flag);
		flag >>= 2;
	}
	flag = 0x40000000;
	printf("\n");
	printf("该整形数中的奇数序列为：\n");
	while (flag)
	{
		printf("%d ", (flag&value)/flag);
		flag >>= 2;

	}
	printf("\n");
}

int main()
{
	int c = 1234;
	print_int_bits_odd_even(c);
	return 0;
}