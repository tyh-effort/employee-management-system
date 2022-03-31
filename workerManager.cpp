#include "workerManager.h" 
WorkerManager::WorkerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、文件存在，并且已经记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();

	//测试代码
	/*
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout <<"编号"<< this->m_EmpArray[i]->m_Id << " "
			<<"姓名" << this->m_EmpArray[i]->m_Name << " "
			<<"职位" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//显示菜单函数
void WorkerManager::Show_Menu()
{
	cout << "******************************************" << endl;
	cout << "********** 欢迎使用员工管理系统 **********" << endl;
	cout << "************* 0.退出管理程序 *************" << endl;
	cout << "************* 1.增加职工信息 *************" << endl;
	cout << "************* 2.显示职工信息 *************" << endl;
	cout << "************* 3.删除离职员工 *************" << endl;
	cout << "************* 4.修改职工信息 *************" << endl;
	cout << "************* 5.查找职工信息 *************" << endl;
	cout << "************* 6.按照编号排序 *************" << endl;
	cout << "************* 7.清空所有文档 *************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

//退出系统函数
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); //退出程序
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入要添加员工人数：" << endl;

	int addNum;
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum; //新空间人数=原空间人数+新加入人数

		//开辟新空间
		Worker ** newSpace = new Worker* [newSize];

		//将原来空间下数据拷贝到新空间
		if (this->m_EmpNum != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择
			int ret=0;
		    do
			{
				cout << "请输入第" << i + 1 << "个新员工编号:";
				cin >> id;
				ret = this->IsExist(id);
				if (ret != -1)
				{
					cout << "输入编号重复请重新输入!" << endl;
				}
			} while (ret != -1);

			cout << "请输入第" << i + 1 << "个新员工名字:";
			cin >> name;

			cout << "岗位列表：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cout << "请选择该职工岗位:";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
			default:
				break;
			}

			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//成功添加后保存到文件中
		this->save();

		//提示添加成功
		cout << "成功添加" <<addNum<<"个新员工！" << endl;
	}
	else {
		cout << "输入数据有误" << endl;
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件  --写文件

	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}

//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //打开文件  --读

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //打开文件  --读

	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;

		if (dId == 1) //利用dId判断是什么员工（普通员工）
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//利用dId判断是什么员工（经理）
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)//利用dId判断是什么员工（总裁）
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	//关闭文件
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;

			break;
		}
	}

	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空!" << endl;
	}
	else {
		//按照职工编号删除
		cout << "请输入想要删除职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id); //调用函数判断是否有这名员工，有返回数组下标，无返回-1

		if (index != -1) //如果职工存在，删除掉index位置上的职工，删除本质是用后面的把要删除的数据覆盖
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--; //更新数组中记录人员个数
			//同步更新数据到文件中
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该员工" << endl;
		}
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空!" << endl;
	}
	else {

		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id); //调用函数判断是否有这名员工，有返回数组下标，无返回-1

		if (ret != -1) //如果职工存在，修改员工信息，本质删除原有的休息添加新信息
		{
			//输出要修改员工信息方便修改
			cout << "查到" << id << "号职工，信息如下：" << endl;

			//调用查询信息接口输出员工信息
			this->m_EmpArray[ret]->showInfo();

			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = " ";
			int dSelect = 0;

			cout << "请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "岗位列表：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cout << "请选择该职工岗位:";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更新数据，到数组指定位置
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

		    //保存到文件中
			this->save();
		}
		else {
			cout << "修改失败，差无此人！" << endl;
		}
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

//查找员工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空!" << endl;
	}
	else {
		cout << "请输入查找的方式:" << endl;
		cout << "1、按职工编号查询" << endl;
		cout << "2、按职工姓名查询" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按照编号查找
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);//调用函数判断是否有这名员工，有返回数组下标，无返回-1
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工信息如下：" << endl;

				//调用查询信息接口输出员工信息
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if(select==2)
		{
			//按照姓名查找
			string name;
			cout << "输入你要查找的姓名：" << endl;
			cin >> name;

			//加入判断是否查到标志
			bool flag = false; //默认等于false，未查到

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" 
						<< this->m_EmpArray[i]->m_Id 
						<< "号职工信息如下" << endl;

					flag = true; //查询到职工后修改判断标志

					//调用查询信息接口输出员工信息
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败查无此人" << endl;
			}
		}
		else {
			cout << "输入有误请重新输入" << endl;
		}
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

//按照编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		//按任意键继续，清屏
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照职工号升序排列" << endl;
		cout << "2、按照职工号降序排列" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i; //声明最小值 或者 最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)//降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else {
					cout << "输入错误！" << endl;

					//按任意键继续，清屏
					system("pause");
					system("cls");

					return;
				}
			}

			//判断一开始认定的 最小值或者最大值 是不是 计算的最小值或者最大值，如果不是 交换数据
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;
		this->save(); //排序的结果保存到文件中
		this->Show_Emp(); //展示所有职工
	}
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空吗？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;
	int select = 0;
	cin >> select;

	if (select == 1) //清空文件
	{
		ofstream ofs(FILENAME, ios::trunc); //删除文件后重新创建文件
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每一个对象
			for(int i=0;i<m_EmpNum;i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	else {
		cout << "取消成功" << endl;
	}
	//按任意键继续，清屏
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray!=NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
	}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
}