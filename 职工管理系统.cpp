#include <iostream> //�������������ͷ
using namespace std; //ʹ�ñ�׼�����ռ�
#include "workerManager.h"
#include "employee.h"
#include "worker.h"
#include "manager.h"
#include "boss.h"

int main()
{
	/*
	//����
	Worker * worker = NULL;
	worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(1, "����", 1);
	worker->showInfo();
	delete worker;

	worker = new Boos(1, "����", 1);
	worker->showInfo();
	delete worker;
	*/

	//ʵ�����������
	WorkerManager wm;

	int choice = 0;

	while (true)
	{
		//������ʾ�˵�����
		wm.Show_Menu();

		cout << "����������ѡ��:";
		cin >> choice;

		switch(choice)
		{
		case 0: //�˳��������
			wm.ExitSystem();
			break;
		case 1: //����ְ����Ϣ
			wm.Add_Emp();
			break;
		case 2: //��ʾְ����Ϣ
			wm.Show_Emp();
			break;
		case 3: //ɾ����ְԱ��
			wm.Del_Emp();
			break;
		case 4: //�޸�ְ����Ϣ
			wm.Mod_Emp();
			break;
		case 5: //����ְ����Ϣ
			wm.Find_Emp();
			break;
		case 6: //���ձ������
			wm.Sort_Emp();
			break;
		case 7: //��������ĵ�
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