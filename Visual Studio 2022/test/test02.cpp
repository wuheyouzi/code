#include <iostream>
using namespace std;

void change(int& a, int& b)
{
	a = 1;
	b = 2;
}

void MySwap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main02()
{
	int a = 10;
	int& b = a;
	change(a, b);

	cout << a << " " << b << endl;

	int c = 100, d = 200;
	MySwap(c, d);
	cout << c << " " << d << endl;

	system("pause");

	return 0;
}