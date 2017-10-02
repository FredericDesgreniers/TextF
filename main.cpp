#include <fstream>
#include <iostream>
#include <sstream>
#include <winuser.h>
#include <wincon.h>
#include "TextTree.h"
#include "ConsoleTextRenderer.h"

TextTree *textTree;

void redrawText()
{
	HWND consoleHandle = GetConsoleWindow();
	HDC consoleDC = GetDC(consoleHandle);

	ConsoleTextRenderer renderer(consoleDC);


	SetTextColor(consoleDC, 0x00FFFFFF);
	SetBkColor(consoleDC, 0x00000000);

	textTree->traverse([&renderer, &consoleDC](Node* node){
		if(node->getValue().length() > 0)
		{
			if (node->getValue().compare("\n") == 0)
			{
				renderer.nextLine();
			} else
			{
				if (node->getCursorPos() >= 0)
				{
					if(node->getCursorPos() > 0)
					{
						std::string textBeforeCursor = node->getValue().substr(0, node->getCursorPos());
						renderer.drawTextToCurrentLine(textBeforeCursor.c_str(), textBeforeCursor.size());
					}

					COLORREF fontColor = SetTextColor(consoleDC, 0x00000000);
					COLORREF backgroundColor = SetBkColor(consoleDC, 0x00FFFFFF);
					std::string value = node->getValue();
					const char c = value.at(node->getCursorPos());
					renderer.drawTextToCurrentLine(&c, 1);
					SetTextColor(consoleDC, fontColor);
					SetBkColor(consoleDC, backgroundColor);

					if(node->getCursorPos() < value.size()-1)
					{
						std::string textAfterCursor = node->getValue().substr(node->getCursorPos() + 1);
						renderer.drawTextToCurrentLine(textAfterCursor.c_str(), textAfterCursor.size());
					}

				} else
				{
					renderer.drawTextToCurrentLine(node->getValue().c_str(), node->getValue().size());
				}
			}
		}
	});
}

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

		redrawText();
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




	if(SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, NULL, 0))
	{

	}


	redrawText();

	MSG msg;
	while(GetMessage( &msg, NULL, 0, 0 ))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	std::cin.get();
}