// #include <iostream>
// using namespace std;
//
// class Person01
// {
// 	int m_A; // 非静态成员b变量，属于类对象上
//
// 	static int m_B; // 静态成员变量，不属于类对象上
//
// 	void func() {}; // 非静态成员函数，不属于类对象上
//
// 	static void func2() {}; // 静态成员函数，不属于类对象上a
// };
// int Person01::m_B = 0;
//
// void test01()
// {
// 	Person01 p;
//
// 	cout << "size of p = " << sizeof(p) << endl; // 一个字节，区分空对象占内存的位置
// }
//
// void test02()
// {
// 	Person01 p;
//
// 	cout << "size of p = " << sizeof(p) << endl;
// }
//
// int main01()
// {
// 	test02();
//
// 	system("pause");
//
// 	return 0;
// }