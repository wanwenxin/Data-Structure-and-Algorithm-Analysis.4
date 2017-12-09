#pragma once
#include <fstream>
#include <iostream>
using namespace std;

ifstream infile;       //输入源文件
ofstream outfile;      //输出目标文件

void readname()
{
	char *inFile = new char[200];       //分配源文件名空间
	char *outFile = new char[200];      //分配目标文件名空间

										//获取源文件
	cout << "Enter source file name :";
	while (1)            //重复输入文件，检验，直到输入文件存在时停止
	{
		gets_s(inFile, 200);      //获取源文件名
		infile.open(inFile, ios::in | ios::binary);      //打开当前源文件对象
		if (infile.fail())        //如果文件不存在
		{
			cout << "The current file does not exist, please re-enter the source file name:";
			infile.close();
		}
		else break;   //源文件存在时，跳出循环
	}

	//获取目标文件
	cout << "Enter the name of the target file :";
	gets_s(outFile, 200);
	outfile.open(outFile, ios::out | ios::app | ios::binary);  //打开目标文件，输出方式打开，不清除原文件并定位到文件尾

															   //此函数只打开文件，未关闭
}

void close_file()
{
	infile.close();    //关闭待处理文件
	outfile.close();   //关闭生成文件
}
