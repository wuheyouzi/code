#include <iostream>
#include <graphics.h>
#include <conio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define NUM 7
#define WIDTH 100
#define HEIGHT 500


const int qupu[] = {
	1,1,5,5,6,6,5,0,0,0,0,
	4,4,3,3,2,2,1,0,0,0,0,
	5,5,4,4,3,3,2,0,0,0,0,
	5,5,4,4,3,3,2,0,0,0,0
};
int cnt;

IMAGE down;
IMAGE img[NUM];

HWND hwnd;

int n = 0;

void initGame();

void showGame();

void playMusic(int index);

void ctolGame();

void timeProc();

int main()
{
	initGame();

	SetTimer(hwnd, 9527, 50, (TIMERPROC)timeProc);
	while (true)
	{
		showGame();
		ctolGame();
	}
	
	system("pause");
	return 0;
}

void timeProc()
{
	SendMessage(hwnd, WM_KEYDOWN, (WPARAM)(qupu[n] + 48), NULL);

	n++;

	if (n >= cnt)
		n = 0;
}

void initGame()
{
	// 1. 做窗口
	hwnd = initgraph(NUM * WIDTH, HEIGHT, SHOWCONSOLE);

	// 2. 播放音乐 界面
	char buff[256];
	for (int i = 0; i < NUM; i++)
	{
		memset(buff, 0, 256);
		sprintf(buff, "images\\%d.bmp", i + 1);
		loadimage(img + i, buff, WIDTH, HEIGHT, true);
	}
	loadimage(&down, "images\\down.bmp", WIDTH, HEIGHT, true);

	cnt = sizeof(qupu) / sizeof(qupu[0]);
}

void showGame()
{
	for (int i = 0; i < NUM; i++)
	{
		putimage(i * WIDTH, 0, img + i);
	}
}

void playMusic(int index)
{
	char buff[256];
	sprintf(buff, "open %d.mp3 alias m", index);
	mciSendString(buff, NULL, NULL, NULL);
	mciSendString("play m", NULL, NULL, NULL);
	putimage((index - 1) * WIDTH, 0, &down);
	Sleep(50);
	putimage((index - 1) * WIDTH, 0, img + index - 1);
	Sleep(300);
}

void ctolGame()
{
	int n;
	// scanf("%d", &n);
	n = _getch();
	printf("n:%d\n", n);

	playMusic(n - 48);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)playMusic, (LPVOID)(n - 48), NULL, NULL);
}