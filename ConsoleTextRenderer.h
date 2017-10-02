//
// Created by frede on 2017-10-02.
//


#pragma once


#include <windef.h>
#include "TextRenderer.h"

class ConsoleTextRenderer : public TextRenderer
{
private:
	HDC consoleDC;
	long lineHeight = 0;
	int currentRow = 0;
	int currentCol = 0;
public:
	ConsoleTextRenderer(HDC consoleDC);

	void drawTextToCurrentLine(const char* text, int length);

	void drawText(const char* string, int length, int x, int y, int width, int height);
	void nextLine();
};




