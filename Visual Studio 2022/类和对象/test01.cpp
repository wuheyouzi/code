#include <iostream>
using namespace std;

const double PI = 3.14; // Ô²ÖÜÂÊ

class Circle
{
public:
	int m_r; // °ë¾¶
	double calculateZC() {
		return 2 * PI * m_r;
	}
};

int main01()
{
	Circle c1;
	c1.m_r = 10;
	
	cout << c1.calculateZC() << endl;

	system("pause");
	
	return 0;
}