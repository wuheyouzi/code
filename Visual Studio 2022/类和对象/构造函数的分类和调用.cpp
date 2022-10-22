#include <iostream>
using namespace std;

class Person02
{
public:
	Person02()
	{
		cout << "Person02无参构造函数的调用" << endl;
	}

	Person02(int a)
	{
		age = a;
		cout << "Person02有参构造函数的调用" << endl;
	}
	// 拷贝构造函数
	Person02(const Person02& p)
	{
		age = p.age;
		cout << "Person02拷贝构造函数调用" << endl;
	}

	~Person02()
	{
		cout << "Person02的析构函数调用" << endl;
	}
	
	int age;
};

void test02()
{
	// 括号法
	Person02 p1; // 默认构造函数调用
	//Person02 p1(); // 编译器认为这是函数声明
	Person02 p2(10); // 有参构造函数
	Person02 p3(p2); // 拷贝构造函数

	cout << "p2的年龄：" << p2.age << endl;
	cout << "p3的年龄：" << p3.age << endl;

	// 显示法
	Person02 p4;
	Person02 p5 = Person02(10);
	Person02 p6 = Person02(p5);
	// Person02(10) 匿名对象，语句执行后系统立马回收内存

	// Person02 (p3); // 不要用拷贝构造函数初始化匿名对象 编译器认为 Person02(p3) == Person02 p3 造成错误：重定义

	// 隐式转换法
	Person02 p7 = 10; // 相当于 Person02 p7 = Person02(10);
	Person02 p8 = p7;
}

int main07()
{
	test02();

	system("pause");

	return 0;
}