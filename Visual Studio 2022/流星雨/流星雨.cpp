#include <iostream>
#include <easyx.h>
#include <time.h>
#include <conio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define STAR_NUM 500
#define METEOR_NUM 25

using namespace std;

struct Star // 小星星
{
	int x;
	int y;
	int r;
	int speed; // 速度
	COLORREF color; // 颜色
};
struct Meteor
{
	int x;
	int y;
	int speed;
	IMAGE *MeteorImg;
};
struct Star star[STAR_NUM];
struct Meteor meteor[METEOR_NUM];

/* @小星星 */
// 初始化星星
void initStar(int i)
{
	star[i].x = rand() % getwidth();
	star[i].y = rand() % getheight();
	star[i].r = rand() % 3 + 1;
	star[i].speed = rand() % 5; // 0 1 2 3 4
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}
// 绘制星星
void drawStar()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		// putpixel(star[i].x, star[i].y, star[i].color);
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].r);
	}
}
// 移动星星
void moveStar()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		star[i].x += star[i].speed;
		if (star[i].x > getwidth())
		{
			star[i].x = 0;
		}
	}
}

/*@流星揍你*/
IMAGE img[2];
IMAGE bk;
void loadImg()
{
	loadimage(img, _T("./1.jpg"), 50, 50);
	loadimage(img + 1, _T("./2.jpg"), 50, 50);
}
void initMeteor(int i)
{
	meteor[i].x = rand() % (2 * getwidth()) - getwidth(); // [-1600, 1600]
	meteor[i].y = 20 - 200;
	meteor[i].speed= rand() % 15 + 1;
	meteor[i].MeteorImg = img + rand() % 2;
}
// 绘制流星：贴图
void drawMeteor()
{
	for (int i = 0; i < METEOR_NUM; i++)
	{
		putimage(meteor[i].x, meteor[i].y, meteor->MeteorImg, SRCPAINT);
	}
}
// 移动流星
void moveMeteor()
{
	for (int i = 0; i < METEOR_NUM; i++)
	{
		meteor[i].x += meteor[i].speed;
		meteor[i].y += meteor[i].speed;
		if (meteor[i].x > getwidth() || meteor[i].y >= getheight())
		{
			initMeteor(i);
		}
	}
}

void welcome()
{
	// 播放音乐
	mciSendString(_T("open ./昼夜-星空.mp3"), NULL, 0, NULL);
	mciSendString(_T("play ./昼夜-星空.mp3 repeat"), NULL, 0, NULL);

	// 设置随机数种子
	srand((unsigned)time(NULL));

	// 设置背景模式
	setbkmode(TRANSPARENT);

	// 设置文字样式
	settextstyle(40, 0, _T("Consolas"));

	// 如果没有按键按下，就一直循环
	while (!_kbhit())
	{
		// 清屏
		cleardevice();
		// 放背景图
		putimage(0, 0, &bk);
		// 设置标题文字样式
		settextstyle(40, 0, _T("Consolas"));
		// 输出文字
		int tx = (getwidth() - textwidth(_T("starry sky"))) / 2;
		outtextxy(tx - 5, 50, _T("starry sky"));

		// 设置文字颜色
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		// 设置正文文字颜色
		settextstyle(40, 0, _T("华文行楷"));
		// 正文
		outtextxy(tx, 150, _T("星空下"));
		outtextxy(tx, 200, _T("是无尽星海"));
		// 结尾
		settextstyle(40, 0, _T("Consolas"));
		outtextxy(tx, 250, _T("--------- star"));

		for (size_t i = 0; i < 10; i++)
		{
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			outtextxy(rand() % getwidth(), rand() % getheight(), _T("🌟"));
		}

		Sleep(930);
	}
}

int main()
{
	// 创建图形窗口
	initgraph(1600, 800);

	// 设置背景颜色
	setbkcolor(RGB(5, 5, 17));
	cleardevice();
	
	loadimage(&bk, _T("./bk.jpg"), getwidth(), getheight());

	for (int i = 0; i < STAR_NUM; i++)
	{
		initStar(i);
	}
	for (int i = 0; i < METEOR_NUM; i++)
	{
		initMeteor(i);
	}
	loadImg();

	welcome();
	 
	// 双缓冲绘图
	BeginBatchDraw();
	
	while (true)
	{
		cleardevice();
		putimage(0, 0, &bk);

		drawStar();
		moveStar();

		drawMeteor();
		moveMeteor();

		FlushBatchDraw();

		Sleep(20);
	}

	EndBatchDraw();
	
	return 0;
}