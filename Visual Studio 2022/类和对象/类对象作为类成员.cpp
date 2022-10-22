#include <iostream>
using namespace std;

class Phone
{
public:
	Phone(string pName) {
		cout << "Phone的构造函数调用" << endl;
		m_PName = pName;
	}
	~Phone()
	{
		cout << "Phone的析构函数调用" << endl;
	}
	// 手机品牌名称
	string m_PName;
};

class Person07
{
public:
	Person07(string name, string pName):m_Name(name), m_Phone(pName) // m_Phone = pName 隐式转化法
	{
		cout << "Person07的构造函数调用" << endl;
	}
	~Person07()
	{
		cout << "Person07的析构函数调用" << endl;
	}
	string m_Name; // 姓名
	Phone m_Phone;
};

void test10()
{
	Person07 p("张三", "苹果MAX");

	cout << p.m_Name << "拿着：" << p.m_Phone.m_PName << endl;
}

int main13()
{
	test10();

	system("pause");

	return 0;
}