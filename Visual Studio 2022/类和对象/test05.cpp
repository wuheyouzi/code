#include <iostream>
using namespace std;

class Persons
{
public:
	// д����

	// ��������
	void SetName(string name) {
		m_Name = name;
	}

	// ��ȡ����
	string GetName()
	{
		return m_Name;
	}

	// ��ȡ����
	int GetAge()
	{
		//m_Age = 0; // ��ʼ��
		return m_Age;
	}

	//��������
	void SetAge(int age) {
		if (age < 0 || age > 150)
		{
			m_Age = 0;
			cout << "�����������" << endl;
			return;
		}
		m_Age = age;
	}
	
	// ����lover
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
	p.SetName("����");

	cout << "����Ϊ��" << p.GetName() << endl;

	p.SetAge(18);
	cout << "����Ϊ��" << p.GetAge() << endl;

	p.SetLover("�־�");

	system("pause");
	return 0;
}