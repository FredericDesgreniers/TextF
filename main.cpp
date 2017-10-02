#include <fstream>
#include <iostream>
#include <sstream>
#include <winuser.h>
#include <wincon.h>
#include "TextTree.h"

TextTree *textTree;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *kbdllhookstruct = (KBDLLHOOKSTRUCT *)lParam;

	if(wParam == WM_KEYDOWN)
	{
		switch (kbdllhookstruct->vkCode)
		{
			case VK_RIGHT:
			{
				textTree->moveCursorRight();
			}break;

			case VK_LEFT:
			{
				textTree->moveCursorLeft();
			}break;
		}
		system("cls");
		textTree->traverse();
	}
}

int main()
{
	std::ifstream inputFile("test.txt");

	std::string line;

	std::stringstream stringBuilder;

	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			stringBuilder << line << "\n";
		}
		inputFile.close();
	}

	std::string s = stringBuilder.str();

	//std::cout << s;

	textTree = new TextTree(s);

	textTree->traverse();

	HANDLE consoleHandle = GetConsoleWindow();
	if(SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, NULL, 0))
	{
		std::cout << "YAY";
	}

	MSG msg;
	while(GetMessage( &msg, NULL, 0, 0 ))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	std::cin.get();
}