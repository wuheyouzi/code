#include <iostream>
using namespace std;

class Phone
{
public:
	Phone(string pName) {
		cout << "Phone�Ĺ��캯������" << endl;
		m_PName = pName;
	}
	~Phone()
	{
		cout << "Phone��������������" << endl;
	}
	// �ֻ�Ʒ������
	string m_PName;
};

class Person07
{
public:
	Person07(string name, string pName):m_Name(name), m_Phone(pName) // m_Phone = pName ��ʽת����
	{
		cout << "Person07�Ĺ��캯������" << endl;
	}
	~Person07()
	{
		cout << "Person07��������������" << endl;
	}
	string m_Name; // ����
	Phone m_Phone;
};

void test10()
{
	Person07 p("����", "ƻ��MAX");

	cout << p.m_Name << "���ţ�" << p.m_Phone.m_PName << endl;
}

int main13()
{
	test10();

	system("pause");

	return 0;
}