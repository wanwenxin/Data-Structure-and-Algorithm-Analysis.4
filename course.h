#pragma once
typedef struct Course
{
	int number = 0;
	char name[50] = { 0 };
	int hours=0;
	int term=0;
	int condition[20] = { 0 };
	int in = 0;
	int sign = 1;//未统计为1
	int start = 0;//可以开始存放的行(0则从首行开始)
}Course;
