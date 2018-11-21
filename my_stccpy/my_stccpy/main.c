#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

char* my_strcpy(char* des_, const char* suc_)
{
	char* ret_ = des_;
	while (*des_=*suc_)
	{
		des_++;
		suc_++;
	}
	return ret_;
}

int main()
{
	char a[] = "i am a student.";
	char b[20];
	my_strcpy(b, a);
	return 0;
}