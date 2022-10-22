#include <iostream>

#include "Class.h"
#include "point.h"

using namespace std;

void isInCircle(Circle& c, Point& p)
{
	int distance = pow((c.GetCenter().GetX() - p.GetX()), 2) + pow((c.GetCenter().GetY() - p.GetY()), 2);

	int RDistance = pow(c.GetR(), 2);

	if (distance == RDistance) {
		cout << "����Բ��" << endl;
	}
	else if (distance > RDistance) {
		cout << "����Բ��" << endl;
	}
	else {
		cout << "����Բ��" << endl;
	}
}

int main()
{
	Circle c;
	c.SetR(10);
	Point center;
	center.SetX(10);
	center.SetY(0);
	c.SetCenter(center);

	Point p;
	p.SetX(10);
	p.SetY(10);

	isInCircle(c, p);

	system("pause");

	return 0;
}