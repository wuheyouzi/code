#include <iostream>
using namespace std;

#define MAX 1000


// �����ϵ�˽ṹ��
struct Person
{
	// ����
	string m_Name;
	// �Ա�
	int m_Sex;
	// ����
	int m_Age;
	// �绰
	string m_Phone;
	//סַ
	string m_Addr;
};

// ͨѶ¼�ṹ��
struct Addressbooks
{
	// ��ϵ������
	struct Person personArray[MAX];
	// ��ǰ��¼����ϵ������
	int m_Size = 0;
};

int GetNumber()
{
	string number;
	cin >> number;
	int len = number.size(), num = 0;
	for (int i = 0; i < len; i++) {
		if (!isdigit(number[i])) {
			return -1;
		}
		num = num * 10 + number[i] - '0';
	}
	return num;
}

// �˵�����
void ShowMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1�������ϵ��  *****" << endl;
	cout << "*****  2����ʾ��ϵ��  *****" << endl;
	cout << "*****  3��ɾ����ϵ��  *****" << endl;
	cout << "*****  4��������ϵ��  *****" << endl;
	cout << "*****  5���޸���ϵ��  *****" << endl;
	cout << "*****  6�������ϵ��  *****" << endl;
	cout << "*****  0���˳�ͨѶ¼  *****" << endl;
	cout << "***************************" << endl;
}

// 1�������ϵ��
void AddPerson(Addressbooks* abs)
{
	// �ж���Ա�Ƿ���
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}

	// ��Ӿ�����ϵ��
	string name;
	cout << "������������" << endl;
	cin >> name;
	abs->personArray[abs->m_Size].m_Name = name;

	// �Ա�
	cout << "�������Ա�" << endl;
	cout << "1 --- ��" << endl;
	cout << "2 --- Ů" << endl;
	int sex = 0;

	while (true)
	{
		sex = GetNumber();
		if (sex == 1 || sex == 2)
		{
			abs->personArray[abs->m_Size].m_Sex = sex;
			break;
		}
		cout << "������������������" << endl;
	}
	
	//����
	cout << "���������䣺" << endl;
	int age = 0;
	while (true)
	{
		age = GetNumber();
		if (age >= 0)
		{
			abs->personArray[abs->m_Size].m_Age = age;
			break;
		}
		cout << "������������������" << endl;
	}
	
	// �绰
	cout << "��������ϵ�绰" << endl;
	string phone;
	cin >> phone;
	abs->personArray[abs->m_Size].m_Phone = phone;

	// סַ
	cout << "�������ͥסַ" << endl;
	string address;
	cin >> address;
	abs->personArray[abs->m_Size].m_Addr = address;

	abs->m_Size++;

	cout << "��ӳɹ�" << endl;
}

void ShowPerson(Addressbooks* abs)
{
	// �ж��Ƿ�Ϊ��
	if (abs->m_Size == 0)
	{
		cout << "��ǰ�ļ�¼Ϊ��" << endl;
		return;
	}

	for (int i = 0; i < abs->m_Size; i++)
	{
		cout << "������" << abs->personArray[i].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << abs->personArray[i].m_Age << "\t";
		cout << "�绰��" << abs->personArray[i].m_Phone << "\t";
		cout << "סַ��" << abs->personArray[i].m_Addr << endl;
	}
}

// �����ϵ���Ƿ����
int isExist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		// �ҵ�
		if (abs->personArray[i].m_Name == name)
		{
			// �ҵ���������������λ��
			return i;
		}
	}
	return -1; // û���ҵ�
}

void deletePerson(Addressbooks* abs)
{
	cout << "��������Ҫɾ������ϵ��" << endl;

	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1)
	{
		// ���ҵ��ˣ�����ɾ��
		for (int i = ret; i < abs->m_Size; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "ɾ���ɹ���" << endl;
	}
	else {
		cout << "���޴���!" << endl;
	}
}

void FindPerson(Addressbooks* abs)
{
	cout << "��������Ҫ���ҵ���ϵ��" << endl;

	string name;
	cin >> name;

	// �жϲ������
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "������" << abs->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << abs->personArray[ret].m_Age << "\t";
		cout << "�绰��" << abs->personArray[ret].m_Phone << "\t";
		cout << "סַ��" << abs->personArray[ret].m_Addr << endl;
	}
	else {
		cout << "���޴���" << endl;
	}
}

// 5���޸�ָ������ϵ����Ϣ
void ModifyPerson(Addressbooks* abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ��" << endl;

	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		// �Ա�
		cout << "�������Ա�" << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		int sex = 0;

		while (true)
		{
			sex = GetNumber();
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}

		//����
		cout << "���������䣺" << endl;
		int age = 0;
		while (true)
		{
			age = GetNumber();
			if (age >= 0)
			{
				abs->personArray[ret].m_Age = age;
				break;
			}
			cout << "������������������" << endl;
		}

		// �绰
		cout << "��������ϵ�绰" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		// סַ
		cout << "�������ͥסַ" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else {
		cout << "���޴���" << endl;
	}
}

// 6�����������ϵ��
void CleanPerson(Addressbooks* abs)
{
	cout << "ȷ�������?" << endl;
	cout << "1����� 2������" << endl;

	int n = 0;

	while (true)
	{
		n = GetNumber();
		if (n == 1)
		{
			abs->m_Size = 0; // �߼���գ�������Ϊ0
			cout << "ͨѶ¼�����" << endl;
			return;
		}
		if (n == 2) return;
		cout << "δ֪ѡ����������룺";
	}
}

int main()
{
	// ����ͨѶ¼
	Addressbooks abs;
	// ��ʼ����Ա����
	abs.m_Size = 0;

	int select = 0;

	while (true)
	{
		// չʾ�˵�
		ShowMenu();

		select = GetNumber();
		cout << endl; // ���Ƹ�ʽ

		switch (select)
		{
		case 1: // 1�������ϵ��
			AddPerson(&abs); // ���õ�ַ����
			break;
		case 2: // 2����ʾ��ϵ��
			ShowPerson(&abs);
			break;
		case 3: // 3��ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4: // 4��������ϵ��
			FindPerson(&abs);
			break;
		case 5: // 5���޸���ϵ��
			ModifyPerson(&abs);
			break;
		case 6: // 6�������ϵ��
			CleanPerson(&abs);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			return 0;
		default:
			cout << "δ֪��ѡ�" << endl;
			break;
		}
		cout << endl; // ���Ƹ�ʽ

		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}