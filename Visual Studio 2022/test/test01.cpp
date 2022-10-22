#include <iostream>
using namespace std;

int* func()
{
	int* p =  new int(100);
	return p;
}

void function()
{
	int* p = new int(100);
	int a = 100;
}

void test01()
{
	int* arr = new int[10];

	for (int i = 0; i < 10; i++)
		arr[i] = i + 100;

	for (int i = 0; i < 10; i++)
		cout << arr[i] << endl;

	delete[] arr;
}

int main01()
{
	int* p = func();
	delete p;
	test01();

	system("pause");

	return 0;
}
