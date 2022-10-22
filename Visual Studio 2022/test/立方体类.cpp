#include <iostream>
using namespace std;

class Cube
{
public:
	// 设置长
	void SetL(int l) {
		m_L = l;
	}
	// 获取长
	int GetL() {
		return m_L;
	}
	// 设置宽
	void SetW(int w) {
		m_W = w;
	}
	// 获取宽
	int GetW() {
		return m_W;
	}
	// 设置高
	void SetH(int h) {
		m_H = h;
	}
	// 获取高
	int GetH() {
		return m_H;
	}
	// 获取立方体表面积
	int CalculateS() {
		return 2 * m_L * m_W + 2 * m_W * m_H + 2 * m_L * m_H;
	}
	// 获取立方体体积
	int CalculateV()
	{
		return m_L * m_W * m_H;
	}
	bool isSameByClass(Cube &c)
	{
		if (m_L == c.GetL() && m_W == c.GetW() && m_H == c.GetH()) {
			return true;
		}

		return false;
	}

private:
	int m_L; // 长
	int m_W; // 宽
	int m_H; // 高
};


// 判断两个Cube是否相等
bool isSame(Cube& c1, Cube& c2)
{
	if (c1.GetL() == c2.GetL() && c1.GetW() == c2.GetW() && c1.GetH() == c2.GetH()) {
		return true;
	}

	return false;
}

int main08()
{
	Cube c1;
	c1.SetL(10);
	c1.SetW(10);
	c1.SetH(10);

	cout << "c1的面积为：" << c1.CalculateS() << endl;
	cout << "c1的体积为：" << c1.CalculateV() << endl;
	cout << endl;

	Cube c2;
	c2.SetL(10);
	c2.SetW(10);
	c2.SetH(10);

	// 全局函数判断
	bool ret = isSame(c1, c2);
	if (ret) {
		cout << "全局函数判断：c1和c2是相等的" << endl;
	}
	else {
		cout << "全局函数判断：c1和c2是不相等的" << endl;
	}

	// 成员函数判断
	ret = c1.isSameByClass(c2);
	if (ret) {
		cout << "全局函数判断：c1和c2是相等的" << endl;
	}
	else {
		cout << "全局函数判断：c1和c2是不相等的" << endl;
	}

	cout << endl;

	system("pause");

	return 0;
}