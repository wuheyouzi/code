#include <iostream>
using namespace std;

class Person05
{
public:
	Person05()
	{
		cout << "Person05Ĭ�Ϲ��캯���ĵ���" << endl;
	}

	Person05(int age, int height)
	{
		m_Age = age;
		m_Height = new int(height);
		cout << "Person05�вι��캯���ĵ���" << endl;
	}

	Person05(const Person05& p)
	{
		cout << "Person05�������캯������" << endl;
		m_Age = p.m_Age;
		m_Height = new int(*p.m_Height);
	}

	~Person05()
	{
		// �����������������������ͷŲ���
		if (m_Height != NULL) {
			delete m_Height;
			m_Height = NULL;
		}
		cout << "Person05��������������" << endl;
	}

	int m_Age;
	int* m_Height;
};

void test08()
{
	Person05 p1(18, 160);

	cout << "p1������Ϊ��" << p1.m_Age << " ���Ϊ��" << *p1.m_Height << endl;

	Person05 p2(p1); // ���������Ŀ�������ǳ������������ɶ����ڴ��ظ��ͷ�

	cout << "p2������Ϊ��" << p2.m_Age << " ���Ϊ��" << *p2.m_Height << endl;

}

int main14()
{
	test08();

	system("pause");

	return 0;
}
