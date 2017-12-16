#pragma once
#include"course.h"
#include"readname.h"
#include<stdio.h> 
#include<cstdlib>
#include<fstream>
#include<iostream>
#include <math.h>
#include <string>
#define N 50 
#define maxsize 1000        //数组大小的最大值  
using namespace std;

class topo
{
public:
	char temp[maxsize];
	int cur;
	int all;
	int a1, a2, a3, a4, a5, a6, a7, a8;
	int table[N];//存入总顺序表
	int over = 0;//over为0则当前循环无存入数据，结束循环
	Course course[N];
public:
	void read(Course course[], char temp[]);//读取
	int read_num(char temp[], int &pos);
	void find(Course course[], char temp[],int cur);

	void sort(Course course[], int table[]);//排序
	void cancel(int cur,int j);//结算入度

	void output(int table[]);//输出
};

void topo::read(Course course[], char temp[])
{
	cout << "---------------------------------------------------------------------" << endl;
	all = 0;
	cur = 1;//从[1]开始存数据
	infile.seekg(0, ios::beg);
	while (!infile.eof())
	{
		infile.getline(temp, 1000, '\n');   //读入当前行内容
		cout << temp << endl;
		find(course,temp,cur);
		all++;
		cur++;
	}
	cout << "---------------------------------------------------------------------" << endl;
	while (1)
	{
		cout << "输入8个学期对应的课程数，空格隔开（例如：6 7 3 6 5 5 5 1）：";
		cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8;
		if (a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 == all)
		{
			break;
		}
		else cout << "总课程数错误";
	}
}

int topo::read_num(char temp[], int  &pos)
{
	int sum=0;
	while (temp[pos] >='0' && temp[pos] <= '9')
	{
		sum *= 10;
		sum += temp[pos] - '0';
		pos++;
	}
	return sum;
}


void topo::find(Course course[], char temp[], int cur)//依次读入 int课程编号 char*课程名称 int学时数 int指定开课学期 int*先决条件
{
	int pos = 0;
	while (temp[pos] == ' ')pos++;  //跳过空格
	if (temp[pos] == 'c')//读入课程编号
	{
		++pos;//跳过'c'
		int num = read_num(temp, pos);
		course[cur].number = num;
	}
	while (temp[pos] == ' ')pos++;  //跳过空格
	if (1)//读入课程名称
	{
		int i;
		for (i = 0;temp[pos]!=' ';i++)
		{
			course[cur].name[i] = temp[pos];
			pos++;
		}
		course[cur].name[i] = '\0';
	}
	while (temp[pos] == ' ')pos++;  //跳过空格
	if (1)//读入学时数
	{
		int num = read_num(temp, pos);
		course[cur].hours = num;
	}
	while (temp[pos] == ' ')pos++;  //跳过空格
	if (1)//读入指定开课学期
	{
		int num = read_num(temp, pos);
		course[cur].term = num;
	}
	while (temp[pos] == ' ')pos++;  //跳过空格
	for (int i = 0;temp[pos] == 'c';i++)//读入先决条件
	{
		++pos;//跳过'c'
		int num = read_num(temp, pos);
		course[cur].condition[i] = num;
		course[cur].in++;//入度加一
		if (temp[pos] != '\0')
		{
			pos++;  //跳过前提条件间的空格
		}
		else break;
	}
}

void topo::cancel(int cur,int j)
{
	for (int temp_cur = 1;temp_cur <= all;temp_cur++)
	{
		for (int temp_i = 0;course[temp_cur].condition[temp_i] != 0;temp_i++)
		{
			if (course[temp_cur].condition[temp_i] == course[cur].number)
			{
				course[temp_cur].in--;//入度减一
				if (course[temp_cur].start < j+1)
				{
					course[temp_cur].start = j+1;
					if (course[temp_cur].start == 8)
					{
						cout << "error1" << endl;
						exit(0);
					}
				}
				break;
			}
		}
	}
}

void topo::sort(Course course[], int table[])
{
	int temp_table[8][N] = { 0 };
	temp_table[0][a1] = -1;//设置顶点
	temp_table[1][a2] = -1;
	temp_table[2][a3] = -1;
	temp_table[3][a4] = -1;
	temp_table[4][a5] = -1;
	temp_table[5][a6] = -1;
	temp_table[6][a7] = -1;
	temp_table[7][a8] = -1;
	for (cur = 1;cur <= all;cur++)
	{
		if (course[cur].term != 0)//有学期限制的
		{
			if (course[cur].sign == 1)//判明是否统计过
			{
				for (int i = 0;i < N;i++)//存放对应空间
				{
					if (temp_table[course[cur].term - 1][i] == 0)//未存放元素
					{
						temp_table[course[cur].term - 1][i] = course[cur].number;
						course[cur].sign = 0;//已统计
						break;
					}
					if (temp_table[course[cur].term - 1][i+1] == -1)
					{
						cout << "error2" << endl;
						exit(0);
					}
				}
			}
		}
	}//处理完有学期限制的
	while (1)
	{
		int jump = 0;
		over = 0;
		for (cur = 1;cur <= all;cur++)
		{
			jump = 0;
			if (course[cur].in == 0)//入度为0
			{
				if (course[cur].sign == 1)//判明是否统计过
				{
					for (int j = course[cur].start;j<8;j++)//存放对应空间
					{
						for (int i = 0;temp_table[j][i] != -1;i++)
						{
							if (temp_table[j][i] == 0)//未存放元素
							{
								temp_table[j][i] = course[cur].number;
								course[cur].sign = 0;//已统计
								cancel(cur,j);
								over++;
								jump = 1;
							}
							if (jump == 1) break;
							if (j == 7 && temp_table[j][i + 1] == -1)
							{
								cout << "error3" << endl;
								exit(0);
							}
						}
						if (jump == 1) break;
					}
				}
			}
		}
		if (over == 0) break;
	}
	int table_num = 0;
	for (int j = 0;j < 8;j++)//存放对应空间
	{
		for (int i = 0;temp_table[j][i] != -1;i++)
		{
			table[table_num] = temp_table[j][i];
			table_num++;
		}
		table[table_num] = 0;
		table_num++;
	}
	table[table_num-1] = -1;//终止标记
}

void topo::output(int table[])
{
	int term = 1;
	cout << "第一学期：";
	for (int i = 0;table[i] != -1;i++)
	{
		if (table[i] != 0)
		{
			cout << course[table[i]].name << " ";
		}
		else
		{
			++term;
			cout << endl;
			if (term == 2)
			{
				cout << "第二学期：";
			}
			if (term == 3)
			{
				cout << "第三学期：";
			}
			if (term == 4)
			{
				cout << "第四学期：";
			}
			if (term == 5)
			{
				cout << "第五学期：";
			}
			if (term == 6)
			{
				cout << "第六学期：";
			}
			if (term == 7)
			{
				cout << "第七学期：";
			}
			if (term == 8)
			{
				cout << "第八学期：";
			}
		}
	}
	cout << endl;
}
