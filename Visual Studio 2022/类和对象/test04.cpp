#include <iostream>
using namespace std;

class C1
{
	int m_A;
};

struct C2
{
	int m_A;
};

int main04()
{
	// struct 默认权限 公共 public
	// class 默认权限 私有 private

	C1 c1;
	//c1.m_A = 100;

	C2 c2;
	c2.m_A = 100;

	return 0;
}