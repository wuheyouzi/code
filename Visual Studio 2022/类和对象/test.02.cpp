#include <iostream>
using namespace std;

class Student
{
public:
	string m_Name;
	int m_Id;

	// 显示信息
	void ShowStudent()
	{
		cout << "姓名：" << m_Name << endl;
		cout << "学号：" << m_Id << endl;
		cout << endl;
	}
	
	// 给姓名赋值
	void SetName(string name) {
		m_Name = name;
	}

	// 给学号赋值
	void SetId(int id) {
		m_Id = id;
	}
};

int main02()
{
	Student s1;
	// s1.m_Name = "张三";
	s1.SetName("张三");
	// s1.m_Id = 1;
	s1.SetId(1);

	s1.ShowStudent();

	Student s2;
	// s2.m_Name = "李四";
	s2.SetName("李四");
	// s2.m_Id = 2;
	s2.SetId(2);

	s2.ShowStudent();

	system("pause");
	return 0;
}