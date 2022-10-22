#include <iostream>
using namespace std;

void func(int& a)
{
	cout << "func(int& a)" << endl;
}

void func(const int& a)
{
	cout << "func(const int& a)" << endl;
}

void func2(int a)
{
	cout << "func2(int a)" << endl;
}

void func2(int a, int b = 10)
{
	cout << "func2(int a, int b = 10)" << endl;
}

int main06()
{
	int a = 10;
	func(a);
	
	func(10); // Ctrl+K+C×¢ÊÍ Ctrl+K+UÈ¡Ïû

	//func2(10);
	func2(10, 100);

	system("pause");

	return 0;
}