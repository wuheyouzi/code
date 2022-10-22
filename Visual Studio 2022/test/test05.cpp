#include <iostream>
using namespace std;

void func()
{
	cout << "func" << endl;
}

void func(int a)
{
	cout << "func(int a)" << endl;
}

void func(double a)
{
	cout << "func(double a)" << endl;
}

void func(int a, double b)
{
	cout << "func(int a, double b)" << endl;
}

void func(double a, int b)
{
	cout << "func(double a, int b)" << endl;
}


int main05()
{
	func();
	func(1);
	func(1.1);
	func(1, 1.1);
	func(1.1, 1);

	system("pause");

	return 0;
}