#include <iostream>
#include <graphics.h> //图形界面
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>
#include <conio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")  //有些东西会报错

#define NUM 13
#define PI 3.14

// 烟花弹的结构体
struct Jet
{
	int x, y; // 坐标
	int hx, hy;  // 最高点
	int height;
	bool shoot; // 空中状态，是否达到最高点
	DWORD t1, t2, dt; // 模拟爆炸过程中时间，速度
	IMAGE img[2];
	byte n : 1;
} jet[NUM];

// 烟花结构体
struct Fire
{
	int r;
	int maxr;
	int x, y; // 坐标
	int cen_x, cen_y; // 中心点，后面用得上
	int width, height; // 图片大小
	int xy[240][240]; // 240 * 240
	bool show;
	bool draw;
	DWORD t1, t2, dt; // 模拟爆炸过程会用到的速度等参数
} fire[NUM];

void Init(int i); // 初始化
void Load();  // 加载图片音乐
void ChoiseRelu(DWORD& t1);
void Shoot();
void ShowFire(DWORD* pmem);
void Style(DWORD& st1);
void saySomething();

int main()
{
	// 窗口初始化
	initgraph(1200, 600);
	srand((unsigned)time(0)); // 随机种子
	// music
	mciSendString(L"open bk.mp3 alias music", 0, 0, 0);//open bgm
	mciSendString(L"play music repeat", 0, 0, 0); // 播放

	saySomething();

	DWORD t1 = timeGetTime();
	DWORD* pmem = GetImageBuffer();
	DWORD st1 = timeGetTime();

	// 初始化
	for (int i = 0; i < NUM; i++)
		Init(i);

	// 加载
	Load();
	Sleep(500);

	// 主程序开始调用
	BeginBatchDraw();
	while (true)
	{
		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 600;
				pmem[py1 * 1200 + px1] = pmem[py1 * 1200 + px1 + 1] = BLACK;
			}
		}
		ChoiseRelu(t1);
		Shoot();
		ShowFire(pmem);
		Style(st1);
		FlushBatchDraw();
	}
	EndBatchDraw();

	return 0;
}

const int r[NUM] = { 120,120,155,123,130,147,138,138,130,135,140,132,155 };
const int x[NUM] = { 120,120,110,117,110,93,102,102,110,105,100,108,110 };
const int y[NUM] = { 120,120,85,118,120,103,105,110,110,120,120,104,85 };

void Init(int i)
{
	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].maxr = r[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();//时间获取速度
	fire[i].r = 0;

	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;
}

void Load()
{
	IMAGE flowerImg, fimg;
	loadimage(&flowerImg, L"flower.jpg", 3120, 240);
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&flowerImg);
		getimage(&fimg, i*240, 0, 240, 240);
		SetWorkingImage(&fimg);
		for (int m = 0; m < 240; m++)
		{
			for (int n = 0; n < 240; n++)
				fire[i].xy[m][n] = getpixel(m, n);
		}
	}
	IMAGE shootImg;
	loadimage(&shootImg, L"shoot.jpg", 200, 50);
	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;
		SetWorkingImage(&shootImg);
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
}

void ChoiseRelu(DWORD& t1)
{
	DWORD t2  = timeGetTime();
	if (t2 - t1 > 100)
	{
		int n = rand() % NUM;
		if (jet[n].shoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1180;
			jet[n].y = rand() % 100 + 600;
			jet[n].hx = jet[n].x;
			jet[n].hy = rand() % 400;
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].shoot = true;
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}
		t1 = t2;
	}
}
void Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			
			if (jet[i].y >= jet[i].hy)
			{
				jet[i].y -= 5;
				jet[i].n++;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			//越高越慢
			if (jet[i].y - jet[i].hy * 4 < jet[i].height)
				jet[i].dt = rand() % 4 + 10;
			//登顶
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				fire[i].x = jet[i].x;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
				jet[i].shoot = false;
			}
			jet[i].t1 = jet[i].t2;
		}
	}
}

void ShowFire(DWORD* pmem)
{
	//dt 
	int  drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 65, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		if (fire[i].t2 - fire[i].t1 > fire[i].dt&& fire[i].show == true)
		{
			if (fire[i].r < fire[i].maxr)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
		
			if (fire[i].r >= fire[i].maxr - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
		}


		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));
		
				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;   //blue
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;   //green
					int r = fire[i].xy[x1][y1] >> 16;   //red
		
					int xx = (int)(fire[i].x + fire[i].r * cos(a));
					int yy = (int)(fire[i].y - fire[i].r * sin(a));
		
					//
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx < 1200 && xx>0 && yy > 0 && yy < 600)
					{
						pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}
		
				}
			}
			fire[i].draw = false;
		}
	}
}

void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 > 20000)  //20s
	{
		int  x[NUM] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int  y[NUM] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };

		for (int i = 0; i < NUM; i++)
		{
			jet[i].x = x[i] * 10;
			jet[i].y = (y[i] + 75) * 10;
			jet[i].hx = jet[i].x;
			jet[i].hy = y[i] * 10;

			jet[i].height = jet[i].y - jet[i].hy;
			jet[i].shoot = true;
			jet[i].dt = 7;
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			fire[i].x = jet[i].x + 10;
			fire[i].y = jet[i].hy;
			fire[i].show = false;
			fire[i].r = 0;
		}
		st1 = st2;
	}
}

void saySomething()
{

	settextcolor(YELLOW);   			// 设置要输出的字体颜色 

	for (int i = 0; i < 50; i++)
	{
		//圆心（500,300） 半径150  60个均匀点的x,y
		int x = 500 + int(150 * sin(PI * 2 * i / 60));
		int y = 300 + int(150 * cos(PI * 2 * i / 60));
		cleardevice(); // 清屏

		settextstyle((i + 1) > 40 ? 40 : i + 1, 0, L"楷体"); // 设置字体
		outtextxy(x + 150, y - 180, L"星空下");     //在指定的位置去输出字符
		outtextxy(x + 150, y - 130, L"烟花绽放");
		settextstyle((i + 1) > 40 ? 40 : i + 1, 0, L"Consolas");
		outtextxy(x + 200, y - 50, L"---star");

		Sleep(25);
	}
}