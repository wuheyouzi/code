#include <iostream>
using namespace std;

class Person01
{
public:
	Person01()
	{
		cout << "Person01���캯���ĵ���" << endl;
	}

	~Person01()
	{
		cout << "Person01��������������" << endl;
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