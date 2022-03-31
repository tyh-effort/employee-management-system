#include <iostream> //包含输入输出流头
using namespace std; //使用标准命名空间
#include "workerManager.h"
#include "employee.h"
#include "worker.h"
#include "manager.h"
#include "boss.h"

int main()
{
	/*
	//测试
	Worker * worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Boos(1, "张三", 1);
	worker->showInfo();
	delete worker;
	*/

	//实例化管理对象
	WorkerManager wm;

	int choice = 0;

	while (true)
	{
		//调用显示菜单函数
		wm.Show_Menu();

		cout << "请输入您的选择:";
		cin >> choice;

		switch(choice)
		{
		case 0: //退出管理程序
			wm.ExitSystem();
			break;
		case 1: //增加职工信息
			wm.Add_Emp();
			break;
		case 2: //显示职工信息
			wm.Show_Emp();
			break;
		case 3: //删除离职员工
			wm.Del_Emp();
			break;
		case 4: //修改职工信息
			wm.Mod_Emp();
			break;
		case 5: //查找职工信息
			wm.Find_Emp();
			break;
		case 6: //按照编号排序
			wm.Sort_Emp();
			break;
		case 7: //清空所有文档
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
		//system("pause");
		//system("cls");
	}

	system("pause");

	return 0;
}