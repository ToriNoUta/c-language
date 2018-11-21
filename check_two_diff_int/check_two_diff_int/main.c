#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
int cmp_int(const void* num1_, const void* num2_)
{
	return (*(int*)num1_ - *(int*)num2_);
}
void check_two_diff_int(int* num_, int size_)
{
	int count_ = 0;
	int i_ = 0;
	int x_ = 0;
	int y_ = 0;
	qsort(num_, size_, sizeof(int), cmp_int);
	for(i_ = 0; i_ < size_; i_++)
	{
		count_ ^= num_[i_];
		if (i_ % 2 != 0 && count_ != 0)
		{
			x_ = num_[i_ - 1];
			y_ = num_[i_];
		}
	}
	printf("不成对的两个数为：%d,%d\n", x_, y_);
}

int main()
{
	int num[] = { 1, 3, 4, 3, 1, 5, 6, 5, 7, 4 };
	check_two_diff_int(num, sizeof(num) / sizeof(num[0]));
	return 0;
}