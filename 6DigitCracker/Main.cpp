#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#define WINVER 0x0500

using namespace std;

void toClipboard(HWND hwnd, const std::string &s);
void LeftClick();

int main() {
	cout << "You have 10 seconds to prepare before the automatic scripting. You can always close the Console Program or press \'CTRL + C\'" << endl;
	Sleep(10000);
	string clipboard;
	ifstream __IN;
	__IN.open("list.txt");

	if (__IN.fail()) {
		cerr << "Error opening file." << endl;
		exit(1);
	}

	// prepare vk structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	
	for (int i = 0; i <= 999999; i++) {
		__IN >> clipboard;
		cout << "INDEX: " << i << ", VALUE: " << clipboard << endl;
		// gets the handle for window
		HWND hwnd = GetDesktopWindow();
		// copy to clipboard
		toClipboard(hwnd, clipboard);

		// press field with code input
		// Press the "LMB" key
		LeftClick();

		// Press the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press the "V" key
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(2);

		// Release the "V" key
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(2);

		// Press the "ENTER" key
		ip.ki.wVk = VK_RETURN;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(2);

		// Release the "ENTER" key
		ip.ki.wVk = VK_RETURN;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(2000);

		if (GetAsyncKeyState(VK_ESCAPE)) exit(1);
	}
	return 0;
}

// Clipboard:

void toClipboard(HWND hwnd, const std::string &s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

// LeftClick

void LeftClick()
{
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}