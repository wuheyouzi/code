#include <iostream> // 首先，这是个预处理命令，就是在编译的时候就做的操作
// include 包含，<名称> 表示把系统库中这个文件在编译的时候拷贝到这个文件，左边的就是c++帮我们写好的库，看到了吧，快速跳转就是按住ctrl + 点击这个名字，包含的库里有预编译指令的话就继续做
using namespace std;
// 这个呢，叫使用一个空间里的东西 using 使用 namespace 带名字的空间 std标准，如果不写，那std里定义的东西，你就要让系统知道，是这个命名空间里的，命名空间不知这一种
// 叫使用一个空间里面的东西，using
int main()
{
    int a; // -2147483648
    // 这是啥，定义了一个int类型变量，int类型，在内存中占用四个字节，表示最大2的三十二次方减一 2147483647
    // 定义的时候可以附上初始值
    int b = 1; // 这样的
    cout << b << endl;
    // 输入
    cin >> a;
    cout << a << endl;
    // >> 后面的是输入的东西保存到哪个变量
    cout << "hello, world" << endl;
    // 两个变量可以以前定义
    int c = 1, d;
    cout << 1 + 1 << endl;
    return 0;
}
