#include <iostream>
using namespace std;

int func(int a = 0, int b = 0, int c = 0)
{
	return a + b + c;
}

int func2(int a = 0, int b = 0, int c = 0);
int func2(int a, int b, int c)
{
	return a + b + c;
}

int func3(int a = 0, int = 1)
{
	return a;
}

int function(int a, int b = 0, int c = 0, int d = 0)
{
	return a + b + c + d;
}

int main04()
{
	cout << func() << endl;
	cout << func(1, 2, 3) << endl;

	cout << func2(1, 2, 3) << endl;

	cout << func3() << endl;

	cout << function(1) << endl;
	cout << function(1, 2, 3) << endl;
	cout << function(1, 2, 4) << endl;

	system("pause");

	return 0;
}