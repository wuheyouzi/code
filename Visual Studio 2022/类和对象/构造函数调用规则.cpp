#include <iostream>
using namespace std;

class Person04
{
public:
	Person04()
	{
		cout << "Person04��Ĭ�Ϲ��캯������" << endl;
	}
	
	Person04(int age)
	{
		cout << "Person04���вι��캯������" << endl;
		m_Age = age;
	}

	Person04(const Person04& p)
	{
		cout << "Person04�Ŀ������캯������" << endl;
		m_Age = p.m_Age;
	}
	
	~Person04()
	{
		cout << "Person04��������������" << endl;
	}

	int m_Age;
};

void test06()
{
	Person04 p;
	p.m_Age = 18;

	Person04 p2(p);

	cout << "p2������Ϊ��" << p2.m_Age << endl;
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