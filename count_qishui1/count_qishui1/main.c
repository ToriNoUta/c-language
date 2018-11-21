#define _CRT_SECURE_NO_WARNINGS 1
#include<stdlib.h>
#include<stdio.h>

enum qishui
{
	bottle = 1,
	cola = 2,
	none = 3
};

int cmp_int(const void* p1, void* p2)
{
	return (*(int*)p1 - *(int*)p2);
}

int count_qishui(enum qishui* x_, int size_)
{
	int i_ = 0;
	int check_ = 0;
	int result_ = 0;
	for (i_ = 0; i_ < size_; i_++)
	{
		x_[i_] = cola;
	}
	while (1)
	{
		check_ = 0;
		qsort(x_, size_, sizeof(int), cmp_int);
		for (i_ = 0; i_ < size_; i_++)
		{
			if (x_[i_] == cola)
			{
				x_[i_] = bottle;
				result_++;
				check_++;
			}
			else if (x_[i_] == bottle&&x_[i_ + 1] == bottle)
			{
				x_[i_] = cola;
				x_[i_ + 1] = none;
				check_++;
			}
		}
		if (check_ == 0)
		{
			break;
		}
	}
	return result_;
}

int main()
{
	enum qishui x[20];
	int result = 0;
	result = count_qishui(x, 20);
	printf("20元总共能换汽水瓶数：%d", result);
	return 0;
}