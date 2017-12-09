// Topological_Order.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "readname.h"
#include "topo.h"

void main()
{
	while (1)
	{
		int command;
		cout << "1.contine/start  2.quit" << endl << "please input order:" ;
		cin >> command;
		if (command == 1)
		{
			readname();
			topo course_topo;
			course_topo.read(course_topo.course, course_topo.temp);
			course_topo.sort(course_topo.course, course_topo.table);
			course_topo.output(course_topo.table);
			close_file();
		}
		else if (command == 2)
		{
			exit(0);
		}
		else
		{
			cout << "error" << endl;
		}
	}
}
