#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

void move()
{
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    HWND hwnd;
    //hwnd = FindWindow("", "");
    POINT pt;
    RECT rect;

    while (1)
    {
        srand(time(0));
        hwnd = GetForegroundWindow();
        GetCursorPos(&pt);
        GetWindowRect(hwnd, &rect);
        if (pt.x >= rect.left && pt.x <= rect.right && pt.y >= rect.top && pt.y <= rect.bottom)
        {
            MoveWindow(hwnd, rand() % 1000, rand() % 800, 434, 350, true);
        }
    }
}

int main()
{
//    char path[300] = {R"(D:\CLionProjects\can't_catch\cmake-build-debug\main.exe)"};
//    GetModuleFileName(NULL, path, 300);
//    CopyFile(path, "D:\\测试\\main.exe", 300);
//    HKEY hkey;
//    RegOpenKey(HKEY_CURRENT_USER, "(SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run)", &hkey);
//    RegSetValueEx(hkey, "Windows_main_c++", 0, REG_SZ, reinterpret_cast<const BYTE *>("D:\\Windows_main_c++.exe"), 1);
//    RegCloseKey(hkey);
    FILE* fp = fopen("D:\\main.txt", "r");
    if (fp == NULL)
    {
        MessageBox(NULL, "内容介绍：这是一个窗口移动的程序。\n开始后，请将任意一个窗口缩小，然后体验变化的快乐。\n记录文件放在D盘，名为main.txt\n当没有记录文件时，此程序正常运行\n", "star", MB_OK);
        MessageBox(NULL, "ready?", "star", MB_OK);
//        int ret = MessageBox(NULL, "Are you ready?", "water", MB_YESNO);
//        if (ret == IDYES)
//        {
//            MessageBox(NULL, "well done", "water", MB_OK);
//            mciSendString("open forest.mp3", 0, 0, 0);
//            mciSendString("play forest.mp3", 0, 0, 0);
//        }
//        else
//        {
//            fp = fopen("D:\\测试\\f", "w");
//            fprintf(fp, reinterpret_cast<const char *>('f'), "123456");
//            fclose(fp);
//            move();
//        }
        fp = fopen("D:\\main.txt", "w");
        fprintf(fp, "star");
        fclose(fp);
        move();
    }
    else {
        MessageBox(NULL, "抱歉，你已运行", "star", MB_OK);
        fprintf(fp, "star");
        fclose(fp);
    }
    return 0;
}
