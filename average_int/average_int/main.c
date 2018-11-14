#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int average_int(const int num1_, const int num2_)	
{
	int result_ = (num1_&num2_)+(num1_^num2_)/2;
	return result_;
}

int main()
{
	int a = 13;
	int b = 17;
	int result = average_int(a, b);
	printf("%d + %d = %d",a,b,result);
	return 0;
}