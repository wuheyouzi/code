#include <iostream>
#include <Windows.h>
using namespace std;

void kd(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		keybd_event(s[i], 0, 0, 0);
		keybd_event(s[i], 0, KEYEVENTF_KEYUP, 0);
	}
	Sleep(20);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

void md()
{
	mouse_event(MOUSEEVENTF_XDOWN, 0, 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_XUP, 0, 0, 0, 0);
}

int main()
{
	Sleep(5000);
	cout << "start" << endl;

	while (true)
	{
		md();
		Sleep(1000);
	}

	for (int i = 1; i <= 10000; i++)
	{
		kd("BG");
		cout << "times: " << i << endl;
		Sleep(1000);
	}
	return 0;
}
