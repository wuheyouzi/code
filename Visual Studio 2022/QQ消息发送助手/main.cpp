#include <iostream>
#include <Windows.h>
using namespace std;

// µ¥¼ü
void PressKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);
	Sleep(50);
	keybd_event(vkey, 0, 2, 0);
	Sleep(50);
}

// Ë«¼ü
void PressKey(BYTE vkey1, BYTE vkey2)
{
	keybd_event(vkey1, 0, 0, 0);
	Sleep(50);
	PressKey('V');
	keybd_event(vkey1, 0, 2, 0);
	Sleep(50);
}

int main()
{
	HWND qqhwnd = FindWindow(L"TXGuiFoundation", L"QQ");

	while (true)
	{
		SetForegroundWindow(qqhwnd);

		PressKey(VK_TAB);
		PressKey(VK_TAB);

		do
		{
			PressKey(VK_DOWN);

			PressKey(VK_RETURN);

		} while (qqhwnd != GetForegroundWindow());


		PressKey(VK_CONTROL, 'V');

		PressKey(VK_RETURN);

		PressKey(VK_ESCAPE);
		
	}
	return 0;
}