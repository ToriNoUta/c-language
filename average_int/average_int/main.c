#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//不使用（a+b）/2的方式计算两个数的平均数
//使用位运算的方法：两数二进制中相同部分使用&运算求得，不同部分使用^运算求得
//将相同部分的全部与不同部分的一半相加
int average_int(const int num1_, const int num2_)	
{
	int result_ = (num1_&num2_)+((num1_^num2_)>>1);
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