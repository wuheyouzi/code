#include <iostream>
using namespace std;

class Person08
{
public:
	static int m_A;
private:
	static int m_B;
};

int Person08::m_A = 100;
int Person08::m_B = 100;

void test11()
{
	Person08 p;
	cout << p.m_A << endl;

	Person08 p2;
	p2.m_A = 200;

	cout << p.m_A << endl;
}

void test12()
{
	Person08 p;
	cout << p.m_A << endl;
	cout << Person08::m_A << endl;
}

int main10()
{
	test11();

	test12();

	system("pause");

	return 0;
}