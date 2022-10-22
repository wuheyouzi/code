#include <iostream>
using namespace std;

class Person04
{
public:
	Person04()
	{
		cout << "Person04的默认构造函数调用" << endl;
	}
	
	Person04(int age)
	{
		cout << "Person04的有参构造函数调用" << endl;
		m_Age = age;
	}

	Person04(const Person04& p)
	{
		cout << "Person04的拷贝构造函数调用" << endl;
		m_Age = p.m_Age;
	}
	
	~Person04()
	{
		cout << "Person04的析构函数调用" << endl;
	}

	int m_Age;
};

void test06()
{
	Person04 p;
	p.m_Age = 18;

	Person04 p2(p);

	cout << "p2的年龄为：" << p2.m_Age << endl;
}

void test07()
{
	Person04 p;
}

int main08()
{
	test06();
	test07();

	system("pause");

	return 0;
}