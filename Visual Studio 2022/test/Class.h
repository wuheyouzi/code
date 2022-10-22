#pragma once
#include <iostream>
#include "point.h"

using namespace std;

class Circle
{
public:
	void SetR(int r);
	int GetR();

	void SetCenter(Point center);
	Point GetCenter();

private:
	int m_R; // �뾶

	Point m_Center; // Բ��
};
