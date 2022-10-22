#include <iostream>
using namespace std;

class Person1
{
	// 公共权限 public 类内外可访问 子类可以访问父类内容
	// 保护权限 protected 类内可以访问，类外不能访问 子类可以访问父类内容
	// 私有权限 private 类内可以访问，类外不能访问 子类不可以访问父类内容

public:
	string m_Name;

protected:
	string m_Car;

private:
	string m_Password;

public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}
};

int main03()
{
	Person1 p1;

	p1.m_Name = "李四";
	// p1.m_Car = "奔驰";
	// p1.m_Password = 123;

	p1.func();

	return 0;
}