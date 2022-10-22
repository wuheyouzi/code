#include <iostream>
using namespace std;

class Cube
{
public:
	// ���ó�
	void SetL(int l) {
		m_L = l;
	}
	// ��ȡ��
	int GetL() {
		return m_L;
	}
	// ���ÿ�
	void SetW(int w) {
		m_W = w;
	}
	// ��ȡ��
	int GetW() {
		return m_W;
	}
	// ���ø�
	void SetH(int h) {
		m_H = h;
	}
	// ��ȡ��
	int GetH() {
		return m_H;
	}
	// ��ȡ����������
	int CalculateS() {
		return 2 * m_L * m_W + 2 * m_W * m_H + 2 * m_L * m_H;
	}
	// ��ȡ���������
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
	int m_L; // ��
	int m_W; // ��
	int m_H; // ��
};


// �ж�����Cube�Ƿ����
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

	cout << "c1�����Ϊ��" << c1.CalculateS() << endl;
	cout << "c1�����Ϊ��" << c1.CalculateV() << endl;
	cout << endl;

	Cube c2;
	c2.SetL(10);
	c2.SetW(10);
	c2.SetH(10);

	// ȫ�ֺ����ж�
	bool ret = isSame(c1, c2);
	if (ret) {
		cout << "ȫ�ֺ����жϣ�c1��c2����ȵ�" << endl;
	}
	else {
		cout << "ȫ�ֺ����жϣ�c1��c2�ǲ���ȵ�" << endl;
	}

	// ��Ա�����ж�
	ret = c1.isSameByClass(c2);
	if (ret) {
		cout << "ȫ�ֺ����жϣ�c1��c2����ȵ�" << endl;
	}
	else {
		cout << "ȫ�ֺ����жϣ�c1��c2�ǲ���ȵ�" << endl;
	}

	cout << endl;

	system("pause");

	return 0;
}