#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//��ż��λ������λ���һ�����Ķ���������
void print_int_bits_odd_even(unsigned int value)
{
	unsigned int flag = 0x80000000;
	printf("���������е�ż��λ����Ϊ��\n");
	while(flag)
	{
		printf("%d ", (flag&value)/flag);
		flag >>= 2;
	}
	flag = 0x40000000;
	printf("\n");
	printf("���������е���������Ϊ��\n");
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