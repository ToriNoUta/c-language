#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
int cmp_int(const void* num1_, const void* num2_)
{
	return (*(int*)num1_ - *(int*)num2_);
}
void check_two_diff_int(int* num_,const int size_)
{
	assert(num_);
	int i_ = 0;
	int des_[2] = {0};
	int* pdes_ = des_;
	qsort(num_, size_, sizeof(num_[0]), cmp_int);
	for(i_ = 0; i_ < size_; i_++)
	{
		if (num_[i_ - 1] != num_[i_] && num_[i_] != num_[i_ + 1])
		{
			*pdes_ = num_[i_];
			pdes_++;
		}
	}
	printf("不成对的两个数为：%d,%d\n", des_[0], des_[1]);
}

int main()
{
	int num[] = { 1, 6, 4, 1, 3, 7, 6, 5, 7, 4 };
	check_two_diff_int(num, sizeof(num) / sizeof(num[0]));
	return 0;
}