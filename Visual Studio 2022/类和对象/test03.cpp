#include <iostream>
using namespace std;

class Person1
{
	// ����Ȩ�� public ������ɷ��� ������Է��ʸ�������
	// ����Ȩ�� protected ���ڿ��Է��ʣ����ⲻ�ܷ��� ������Է��ʸ�������
	// ˽��Ȩ�� private ���ڿ��Է��ʣ����ⲻ�ܷ��� ���಻���Է��ʸ�������

public:
	string m_Name;

protected:
	string m_Car;

private:
	string m_Password;

public:
	void func()
	{
		m_Name = "����";
		m_Car = "������";
		m_Password = 123456;
	}
};

int main03()
{
	Person1 p1;

	p1.m_Name = "����";
	// p1.m_Car = "����";
	// p1.m_Password = 123;

	p1.func();

	return 0;
}