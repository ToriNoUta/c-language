#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//ɨ��һ���޷����������Ķ����Ʒ������С�1���ĸ���
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
	printf("c�Ķ������С�1���ĸ���Ϊ��%d", count_one_bits(c));
	return 0;
}