#include <iostream>
using namespace std;

class Student
{
public:
	string m_Name;
	int m_Id;

	// ��ʾ��Ϣ
	void ShowStudent()
	{
		cout << "������" << m_Name << endl;
		cout << "ѧ�ţ�" << m_Id << endl;
		cout << endl;
	}
	
	// ��������ֵ
	void SetName(string name) {
		m_Name = name;
	}

	// ��ѧ�Ÿ�ֵ
	void SetId(int id) {
		m_Id = id;
	}
};

int main02()
{
	Student s1;
	// s1.m_Name = "����";
	s1.SetName("����");
	// s1.m_Id = 1;
	s1.SetId(1);

	s1.ShowStudent();

	Student s2;
	// s2.m_Name = "����";
	s2.SetName("����");
	// s2.m_Id = 2;
	s2.SetId(2);

	s2.ShowStudent();

	system("pause");
	return 0;
}