#include <iostream>
using namespace std;

class Person02
{
public:
	Person02()
	{
		cout << "Person02�޲ι��캯���ĵ���" << endl;
	}

	Person02(int a)
	{
		age = a;
		cout << "Person02�вι��캯���ĵ���" << endl;
	}
	// �������캯��
	Person02(const Person02& p)
	{
		age = p.age;
		cout << "Person02�������캯������" << endl;
	}

	~Person02()
	{
		cout << "Person02��������������" << endl;
	}
	
	int age;
};

void test02()
{
	// ���ŷ�
	Person02 p1; // Ĭ�Ϲ��캯������
	//Person02 p1(); // ��������Ϊ���Ǻ�������
	Person02 p2(10); // �вι��캯��
	Person02 p3(p2); // �������캯��

	cout << "p2�����䣺" << p2.age << endl;
	cout << "p3�����䣺" << p3.age << endl;

	// ��ʾ��
	Person02 p4;
	Person02 p5 = Person02(10);
	Person02 p6 = Person02(p5);
	// Person02(10) �����������ִ�к�ϵͳ��������ڴ�

	// Person02 (p3); // ��Ҫ�ÿ������캯����ʼ���������� ��������Ϊ Person02(p3) == Person02 p3 ��ɴ����ض���

	// ��ʽת����
	Person02 p7 = 10; // �൱�� Person02 p7 = Person02(10);
	Person02 p8 = p7;
}

int main07()
{
	test02();

	system("pause");

	return 0;
}