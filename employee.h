#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream> //�������������ͷ
using namespace std; //ʹ�ñ�׼�����ռ�
#include "worker.h"

//Ա����
class Employee :public Worker
{
public:

	//���캯��
	Employee(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡְ����λ����
	virtual string getDeptName();

};