#include <iostream>
#include <graphics.h>
#include <Windows.h>
#include <string>
#include <mmsystem.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "winmm.lib")

using namespace cv;
using namespace std;

int main()
{
	initgraph(960, 640); // 创建窗口
	setbkcolor(BLACK); // 设置窗口背景颜色为黑色
	cleardevice(); // 刷新
	settextstyle(12, 0, "楷体"); // 设置字体
	setbkmode(TRANSPARENT); // 设置背景模式，去掉文字背景
	settextcolor(WHITE); // 设置文字颜色
	VideoCapture myvideo("./1.mp4"); // 加载视频
	mciSendString("open ./1.mp3 alias bgm", 0, 0, 0); // 打开播放音乐，起了一个音乐的别名
	// 效果好一点，从复杂到简单
	const char* str = "@#$%&!=+*,';+^~.    "; // 替换的字符
	int len = strlen(str);
	BeginBatchDraw();
	Mat frame;
	Mat show;
	String text;
	int index = 0;
	while (true)
	{
		myvideo >> frame;
		if (frame.empty())
			break;

		// 把BGR颜色空间转为GRAY灰度图
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		// 调整图片大小
		resize(frame, show, Size(300, 150));
		resize(frame, frame, Size(150, 50));

		cleardevice();
		for (int x = 0; x < frame.rows; x++)
		{
			for (int y = 0; y < frame.cols; y++)
			{
				int grayval = frame.at<uchar>(x, y);
				index = grayval / 256.0 * len; // 通过颜色比例，把颜色转成字符
				text += str[index];
			}
			outtextxy(0, x * textheight(str[index]), (text.data())); // 逐行输出
			text.clear(); // 每一行清除一次
		}
		imshow(" ", show);

		int key = waitKey(10);
		if (key == 32) // 按空格退出
			break;
		mciSendString("play bgm", 0, 0, 0);
		FlushBatchDraw();
	}

	waitKey(0);
	return 0;
}