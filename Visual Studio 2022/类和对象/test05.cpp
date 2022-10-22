#include <iostream>
using namespace std;

class Persons
{
public:
	// 写姓名

	// 设置姓名
	void SetName(string name) {
		m_Name = name;
	}

	// 获取姓名
	string GetName()
	{
		return m_Name;
	}

	// 获取年龄
	int GetAge()
	{
		//m_Age = 0; // 初始化
		return m_Age;
	}

	//设置年龄
	void SetAge(int age) {
		if (age < 0 || age > 150)
		{
			m_Age = 0;
			cout << "你这个老妖精" << endl;
			return;
		}
		m_Age = age;
	}
	
	// 设置lover
	void SetLover(string lover) {
		m_Lover = lover;
	}

private:
	string m_Name;
	int m_Age;
	string m_Lover;
};

int main06()
{
	Persons p;
	p.SetName("张三");

	cout << "姓名为：" << p.GetName() << endl;

	p.SetAge(18);
	cout << "年龄为：" << p.GetAge() << endl;

	p.SetLover("仓井");

	system("pause");
	return 0;
}