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
	initgraph(960, 640); // ��������
	setbkcolor(BLACK); // ���ô��ڱ�����ɫΪ��ɫ
	cleardevice(); // ˢ��
	settextstyle(12, 0, "����"); // ��������
	setbkmode(TRANSPARENT); // ���ñ���ģʽ��ȥ�����ֱ���
	settextcolor(WHITE); // ����������ɫ
	VideoCapture myvideo("./1.mp4"); // ������Ƶ
	mciSendString("open ./1.mp3 alias bgm", 0, 0, 0); // �򿪲������֣�����һ�����ֵı���
	// Ч����һ�㣬�Ӹ��ӵ���
	const char* str = "@#$%&!=+*,';+^~.    "; // �滻���ַ�
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

		// ��BGR��ɫ�ռ�תΪGRAY�Ҷ�ͼ
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		// ����ͼƬ��С
		resize(frame, show, Size(300, 150));
		resize(frame, frame, Size(150, 50));

		cleardevice();
		for (int x = 0; x < frame.rows; x++)
		{
			for (int y = 0; y < frame.cols; y++)
			{
				int grayval = frame.at<uchar>(x, y);
				index = grayval / 256.0 * len; // ͨ����ɫ����������ɫת���ַ�
				text += str[index];
			}
			outtextxy(0, x * textheight(str[index]), (text.data())); // �������
			text.clear(); // ÿһ�����һ��
		}
		imshow(" ", show);

		int key = waitKey(10);
		if (key == 32) // ���ո��˳�
			break;
		mciSendString("play bgm", 0, 0, 0);
		FlushBatchDraw();
	}

	waitKey(0);
	return 0;
}