#include <iostream>
using namespace std;

class Person03
{
public:
	Person03()
	{
		cout << "Person03默认构造函数的调用" << endl;
	}

	Person03(int age)
	{
		cout << "Person03有参构造函数的调用" << endl;
		m_Age = age;
	}

	Person03(const Person03& p)
	{
		cout << "Person03拷贝构造函数的调用" << endl;
		m_Age = p.m_Age;
	}

	~Person03()
	{
		cout << "Person03的析构函数调用" << endl;
	}

	int m_Age;
};

void test03()
{
	Person03 p1(20);
	Person03 p2(p1);

	cout << "p2的年龄：" << p2.m_Age << endl;
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