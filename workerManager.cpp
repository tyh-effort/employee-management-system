#include "workerManager.h" 
WorkerManager::WorkerManager()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�

	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ����ڣ������Ѿ���¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();

	//���Դ���
	/*
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout <<"���"<< this->m_EmpArray[i]->m_Id << " "
			<<"����" << this->m_EmpArray[i]->m_Name << " "
			<<"ְλ" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//��ʾ�˵�����
void WorkerManager::Show_Menu()
{
	cout << "******************************************" << endl;
	cout << "********** ��ӭʹ��Ա������ϵͳ **********" << endl;
	cout << "************* 0.�˳�������� *************" << endl;
	cout << "************* 1.����ְ����Ϣ *************" << endl;
	cout << "************* 2.��ʾְ����Ϣ *************" << endl;
	cout << "************* 3.ɾ����ְԱ�� *************" << endl;
	cout << "************* 4.�޸�ְ����Ϣ *************" << endl;
	cout << "************* 5.����ְ����Ϣ *************" << endl;
	cout << "************* 6.���ձ������ *************" << endl;
	cout << "************* 7.��������ĵ� *************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ����
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); //�˳�����
}

//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "������Ҫ���Ա��������" << endl;

	int addNum;
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum; //�¿ռ�����=ԭ�ռ�����+�¼�������

		//�����¿ռ�
		Worker ** newSpace = new Worker* [newSize];

		//��ԭ���ռ������ݿ������¿ռ�
		if (this->m_EmpNum != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��
			int ret=0;
		    do
			{
				cout << "�������" << i + 1 << "����Ա�����:";
				cin >> id;
				ret = this->IsExist(id);
				if (ret != -1)
				{
					cout << "�������ظ�����������!" << endl;
				}
			} while (ret != -1);

			cout << "�������" << i + 1 << "����Ա������:";
			cin >> name;

			cout << "��λ�б�" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cout << "��ѡ���ְ����λ:";
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

			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//�ɹ���Ӻ󱣴浽�ļ���
		this->save();

		//��ʾ��ӳɹ�
		cout << "�ɹ����" <<addNum<<"����Ա����" << endl;
	}
	else {
		cout << "������������" << endl;
	}
	//�����������������
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�  --д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}

//ͳ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�  --��

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
		num++;
	}
	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�  --��

	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;

		if (dId == 1) //����dId�ж���ʲôԱ������ͨԱ����
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//����dId�ж���ʲôԱ��������
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)//����dId�ж���ʲôԱ�����ܲã�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�����������������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;

			break;
		}
	}

	return index;
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
	}
	else {
		//����ְ�����ɾ��
		cout << "��������Ҫɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id); //���ú����ж��Ƿ�������Ա�����з��������±꣬�޷���-1

		if (index != -1) //���ְ�����ڣ�ɾ����indexλ���ϵ�ְ����ɾ���������ú���İ�Ҫɾ�������ݸ���
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--; //���������м�¼��Ա����
			//ͬ���������ݵ��ļ���
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
		}
	}
	//�����������������
	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
	}
	else {

		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id); //���ú����ж��Ƿ�������Ա�����з��������±꣬�޷���-1

		if (ret != -1) //���ְ�����ڣ��޸�Ա����Ϣ������ɾ��ԭ�е���Ϣ�������Ϣ
		{
			//���Ҫ�޸�Ա����Ϣ�����޸�
			cout << "�鵽" << id << "��ְ������Ϣ���£�" << endl;

			//���ò�ѯ��Ϣ�ӿ����Ա����Ϣ
			this->m_EmpArray[ret]->showInfo();

			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = " ";
			int dSelect = 0;

			cout << "��������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "��λ�б�" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cout << "��ѡ���ְ����λ:";
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

			//�������ݣ�������ָ��λ��
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

		    //���浽�ļ���
			this->save();
		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	//�����������������
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1����ְ����Ų�ѯ" << endl;
		cout << "2����ְ��������ѯ" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//���ձ�Ų���
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);//���ú����ж��Ƿ�������Ա�����з��������±꣬�޷���-1
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;

				//���ò�ѯ��Ϣ�ӿ����Ա����Ϣ
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if(select==2)
		{
			//������������
			string name;
			cout << "������Ҫ���ҵ�������" << endl;
			cin >> name;

			//�����ж��Ƿ�鵽��־
			bool flag = false; //Ĭ�ϵ���false��δ�鵽

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" 
						<< this->m_EmpArray[i]->m_Id 
						<< "��ְ����Ϣ����" << endl;

					flag = true; //��ѯ��ְ�����޸��жϱ�־

					//���ò�ѯ��Ϣ�ӿ����Ա����Ϣ
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܲ��޴���" << endl;
			}
		}
		else {
			cout << "������������������" << endl;
		}
	}
	//�����������������
	system("pause");
	system("cls");
}

//���ձ������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		//�����������������
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ������������" << endl;
		cout << "2������ְ���Ž�������" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i; //������Сֵ ���� ���ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else {
					cout << "�������" << endl;

					//�����������������
					system("pause");
					system("cls");

					return;
				}
			}

			//�ж�һ��ʼ�϶��� ��Сֵ�������ֵ �ǲ��� �������Сֵ�������ֵ��������� ��������
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save(); //����Ľ�����浽�ļ���
		this->Show_Emp(); //չʾ����ְ��
	}
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	int select = 0;
	cin >> select;

	if (select == 1) //����ļ�
	{
		ofstream ofs(FILENAME, ios::trunc); //ɾ���ļ������´����ļ�
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿһ������
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
		cout << "��ճɹ�" << endl;
	}
	else {
		cout << "ȡ���ɹ�" << endl;
	}
	//�����������������
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