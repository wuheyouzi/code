#include <iostream>
using namespace std;

class Person01
{
public:
	Person01()
	{
		cout << "Person01构造函数的调用" << endl;
	}

	~Person01()
	{
		cout << "Person01的析构函数调用" << endl;
	}
};

void test01()
{
	Person01 p;
}

int main09()
{
	test01();

	Person01 p;

	system("pause");

	return 0;
}