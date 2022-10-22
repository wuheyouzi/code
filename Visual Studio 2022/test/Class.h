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
	int m_R; // °ë¾¶

	Point m_Center; // Ô²ÐÄ
};
