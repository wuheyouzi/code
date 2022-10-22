#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <graphics.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define WIDTH 720
#define HEIGHT 1000

#define IMGW 50
#define IMGH 64

#define Red_Packet 0
#define Bomp 1
#define SPEED 6

#define NUMS 10

IMAGE background;
IMAGE bomp_img[2];
IMAGE packet_img[2];

int count = 0;

struct RedPacket
{
	int x;
	int y;
	int type;
};

struct RedPacket redPacket[NUMS];

void InitData(int pos)
{
	redPacket[pos].x = rand() % (WIDTH - IMGW);
	redPacket[pos].y = rand() % 401 - 500;

	if (rand() % 100 < 80)
	{
		redPacket[pos].type = Red_Packet;
	}
	else
	{
		redPacket[pos].type = Bomp;
	}
}


void DrawRedPacket(RedPacket cur)
{
	switch (cur.type)
	{
	case Red_Packet:
		putimage(cur.x, cur.y, packet_img + 1, SRCAND);
		putimage(cur.x, cur.y, packet_img + 0, SRCPAINT);
		break;
	case Bomp:
		putimage(cur.x, cur.y, bomp_img + 0, SRCAND);
		putimage(cur.x, cur.y, bomp_img + 1, SRCPAINT);
		break;
	default:
		exit(EXIT_FAILURE);
	}
}

void MoveRedPacket()
{
	for (int i = 0; i < NUMS; i++)
	{
		redPacket[i].y += SPEED;
		if (redPacket[i].y >= HEIGHT)
		{
			if (redPacket[i].type == Red_Packet)
				count--;
			InitData(i);
		}
	}
}

void LoadResources()
{
	loadimage(&background, "./res/background.jpg", WIDTH, HEIGHT);

	loadimage(packet_img + 0, "./res/red_packet.jpg", IMGW, IMGH);
	loadimage(packet_img + 1, "./res/red_packet_y.jpg", IMGW, IMGH);

	loadimage(bomp_img + 0, "./res/bomp.jpg", IMGW, IMGH);
	loadimage(bomp_img + 1, "./res/bomp_y.jpg", IMGW, IMGH);
	for (int i = 0; i < NUMS; i++)
	{
		InitData(i);
	}
}

void DrawGame()
{
	putimage(0, 0, &background);
	for (int i = 0; i < NUMS; i++)
	{
		DrawRedPacket(redPacket[i]);
	}
}

int MouseEvent(ExMessage msg)
{
	for (int i = 0; i < NUMS; i++)
	{
		if (msg.x >= redPacket[i].x && msg.x <= redPacket[i].x + IMGW && msg.y >= redPacket[i].y && msg.y <= redPacket[i].y + IMGH)
			return i;
	}
	return -1;
}

int OnTimer(int duration, int id)
{
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration)
	{
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

void ShowRedPacket(int x, int y)
{
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(30, 0, 0);
	char info[20] = "";
	sprintf_s(info, 20, "ºì°ü£º%d", count);
	outtextxy(x, y, info);
}

int main()
{
	LoadResources();
	HWND hd = initgraph(WIDTH, HEIGHT);
	mciSendString("open ./res/1.mp3", 0, 0, 0);
	mciSendString("play ./res/1.mp3 repeat", 0, 0, 0);
	ExMessage msg;
	BeginBatchDraw();
	while (true)
	{
		DrawGame();
		ShowRedPacket(0, 0);
		FlushBatchDraw();

		if (OnTimer(40,0))
			MoveRedPacket();
		while (peekmessage(&msg))
		{
			int pos = MouseEvent(msg);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pos != -1 && redPacket[pos].type == Red_Packet)
				{
					InitData(pos);
					count++;
				}
				else if (pos != -1 && redPacket[pos].type == Bomp)
				{
					mciSendString("open ./res/2.mp3", 0, 0, 0);
					mciSendString("play ./res/2.mp3 repeat wait", 0, 0, 0);
					mciSendString("close ./res/2.mp3", 0, 0, 0);
					MessageBox(hd, "GamOver", "Lost", MB_OK);
					goto end;
				}
			}
		}
	}
	end:
	EndBatchDraw();
	closegraph();
	return 0;
}