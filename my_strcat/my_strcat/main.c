#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>

char* my_strcat(char* des_,const char* suc_)
{
	assert(des_);
	assert(suc_);
	char* ret = des_;
	while (*des_)
	{
		des_++;
	}
	while (*des_ = *suc_)
	{
		des_++;
		suc_++;
	}
	return ret;
}

int main()
{
	char a[20] = "i am ";
	char b[] = "a student.";
	my_strcat(a, b);
	return 0;
}