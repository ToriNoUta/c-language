#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//检查俩整型数二进制位有多少个不同bit
int check_int_def_bin(unsigned int num1,unsigned int num2)
{
	int count = 0;
	unsigned int flag = 0x80000000;
	unsigned int check = num1^num2;
	while (flag)
	{
		if ((flag&check) / flag)
			count++;
		flag >>= 1;
	}
	return count;
}

int main()
{
	int n1 = 0x80000000;
	int n2 = 0x8a0000a8;
	printf("%d ",check_int_def_bin(n1, n2));
	return 0;
}