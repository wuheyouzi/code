#include <iostream>
using namespace std;

class Person05
{
public:
	Person05()
	{
		cout << "Person05默认构造函数的调用" << endl;
	}

	Person05(int age, int height)
	{
		m_Age = age;
		m_Height = new int(height);
		cout << "Person05有参构造函数的调用" << endl;
	}

	Person05(const Person05& p)
	{
		cout << "Person05拷贝构造函数调用" << endl;
		m_Age = p.m_Age;
		m_Height = new int(*p.m_Height);
	}

	~Person05()
	{
		// 析构，将堆区开辟数据做释放操作
		if (m_Height != NULL) {
			delete m_Height;
			m_Height = NULL;
		}
		cout << "Person05的析构函数调用" << endl;
	}

	int m_Age;
	int* m_Height;
};

void test08()
{
	Person05 p1(18, 160);

	cout << "p1的年龄为：" << p1.m_Age << " 身高为：" << *p1.m_Height << endl;

	Person05 p2(p1); // 编译器做的拷贝，叫浅拷贝，但会造成堆区内存重复释放

	cout << "p2的年龄为：" << p2.m_Age << " 身高为：" << *p2.m_Height << endl;

}

int main14()
{
	test08();

	system("pause");

	return 0;
}
