#include <iostream>
using namespace std;

#define MAX 1000


// 设计联系人结构体
struct Person
{
	// 姓名
	string m_Name;
	// 性别
	int m_Sex;
	// 年龄
	int m_Age;
	// 电话
	string m_Phone;
	//住址
	string m_Addr;
};

// 通讯录结构体
struct Addressbooks
{
	// 联系人数组
	struct Person personArray[MAX];
	// 当前记录的联系人数量
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

// 菜单界面
void ShowMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、修改联系人  *****" << endl;
	cout << "*****  6、清空联系人  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}

// 1、添加联系人
void AddPerson(Addressbooks* abs)
{
	// 判断人员是否满
	if (abs->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}

	// 添加具体联系人
	string name;
	cout << "请输入姓名：" << endl;
	cin >> name;
	abs->personArray[abs->m_Size].m_Name = name;

	// 性别
	cout << "请输入性别：" << endl;
	cout << "1 --- 男" << endl;
	cout << "2 --- 女" << endl;
	int sex = 0;

	while (true)
	{
		sex = GetNumber();
		if (sex == 1 || sex == 2)
		{
			abs->personArray[abs->m_Size].m_Sex = sex;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	
	//年龄
	cout << "请输入年龄：" << endl;
	int age = 0;
	while (true)
	{
		age = GetNumber();
		if (age >= 0)
		{
			abs->personArray[abs->m_Size].m_Age = age;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	
	// 电话
	cout << "请输入联系电话" << endl;
	string phone;
	cin >> phone;
	abs->personArray[abs->m_Size].m_Phone = phone;

	// 住址
	cout << "请输入家庭住址" << endl;
	string address;
	cin >> address;
	abs->personArray[abs->m_Size].m_Addr = address;

	abs->m_Size++;

	cout << "添加成功" << endl;
}

void ShowPerson(Addressbooks* abs)
{
	// 判断是否为空
	if (abs->m_Size == 0)
	{
		cout << "当前的记录为空" << endl;
		return;
	}

	for (int i = 0; i < abs->m_Size; i++)
	{
		cout << "姓名：" << abs->personArray[i].m_Name << "\t";
		cout << "性别：" << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
		cout << "年龄：" << abs->personArray[i].m_Age << "\t";
		cout << "电话：" << abs->personArray[i].m_Phone << "\t";
		cout << "住址：" << abs->personArray[i].m_Addr << endl;
	}
}

// 检测联系人是否存在
int isExist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		// 找到
		if (abs->personArray[i].m_Name == name)
		{
			// 找到，返回在数组中位置
			return i;
		}
	}
	return -1; // 没有找到
}

void deletePerson(Addressbooks* abs)
{
	cout << "请输入您要删除的联系人" << endl;

	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1)
	{
		// 查找到人，进行删除
		for (int i = ret; i < abs->m_Size; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "删除成功！" << endl;
	}
	else {
		cout << "查无此人!" << endl;
	}
}

void FindPerson(Addressbooks* abs)
{
	cout << "请输入您要查找的联系人" << endl;

	string name;
	cin >> name;

	// 判断查找情况
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
		cout << "住址：" << abs->personArray[ret].m_Addr << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
}

// 5、修改指定的联系人信息
void ModifyPerson(Addressbooks* abs)
{
	cout << "请输入您要修改的联系人" << endl;

	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		// 性别
		cout << "请输入性别：" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex = 0;

		while (true)
		{
			sex = GetNumber();
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}

		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		while (true)
		{
			age = GetNumber();
			if (age >= 0)
			{
				abs->personArray[ret].m_Age = age;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}

		// 电话
		cout << "请输入联系电话" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		// 住址
		cout << "请输入家庭住址" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else {
		cout << "查无此人" << endl;
	}
}

// 6、清空所有联系人
void CleanPerson(Addressbooks* abs)
{
	cout << "确定清空吗?" << endl;
	cout << "1、清空 2、放弃" << endl;

	int n = 0;

	while (true)
	{
		n = GetNumber();
		if (n == 1)
		{
			abs->m_Size = 0; // 逻辑清空，人数置为0
			cout << "通讯录已清空" << endl;
			return;
		}
		if (n == 2) return;
		cout << "未知选项，请重新输入：";
	}
}

int main()
{
	// 创建通讯录
	Addressbooks abs;
	// 初始化人员个数
	abs.m_Size = 0;

	int select = 0;

	while (true)
	{
		// 展示菜单
		ShowMenu();

		select = GetNumber();
		cout << endl; // 控制格式

		switch (select)
		{
		case 1: // 1、添加联系人
			AddPerson(&abs); // 利用地址传递
			break;
		case 2: // 2、显示联系人
			ShowPerson(&abs);
			break;
		case 3: // 3、删除联系人
			deletePerson(&abs);
			break;
		case 4: // 4、查找联系人
			FindPerson(&abs);
			break;
		case 5: // 5、修改联系人
			ModifyPerson(&abs);
			break;
		case 6: // 6、清空联系人
			CleanPerson(&abs);
			break;
		case 0:
			cout << "欢迎下次使用!" << endl;
			system("pause");
			return 0;
		default:
			cout << "未知的选项！" << endl;
			break;
		}
		cout << endl; // 控制格式

		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}