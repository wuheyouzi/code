#include <iostream>
using namespace std;

class Person03
{
public:
	Person03()
	{
		cout << "Person03Ĭ�Ϲ��캯���ĵ���" << endl;
	}

	Person03(int age)
	{
		cout << "Person03�вι��캯���ĵ���" << endl;
		m_Age = age;
	}

	Person03(const Person03& p)
	{
		cout << "Person03�������캯���ĵ���" << endl;
		m_Age = p.m_Age;
	}

	~Person03()
	{
		cout << "Person03��������������" << endl;
	}

	int m_Age;
};

void test03()
{
	Person03 p1(20);
	Person03 p2(p1);

	cout << "p2�����䣺" << p2.m_Age << endl;
}

void DoWork(Person03 p)
{

}

void test04()
{
	Person03 p;
	DoWork(p);
}

Person03 DoWork2()
{
	Person03 p1;
	return p1;
}

void test05()
{
	Person03 p = DoWork2();
}

int main12()
{
	test03();
	test04();
	test05();

	system("pause");
	return 0;
}