#include <iostream>
using namespace std;

int& test01()
{
	static int a = 10;
	return a;
}

int& test02()
{
	static int a = 100;
	return a;
}

int main03()
{
	int& ref = test01();
	int& ret = test02();
	cout << ref << " " << ret << endl;
	
	test02() = 1000;
	cout << ref << " " << ret << endl;


	system("pause");

	return 0;
}