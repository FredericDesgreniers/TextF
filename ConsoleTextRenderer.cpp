//
// Created by frede on 2017-10-02.
//

#include <wingdi.h>
#include <winuser.h>
#include <iostream>
#include "ConsoleTextRenderer.h"

ConsoleTextRenderer::ConsoleTextRenderer(HDC consoleDC): consoleDC(consoleDC), TextRenderer()
{

}

void ConsoleTextRenderer::drawText(const char *string, int length, int x, int y, int width, int height)
{
	RECT rect = {x ,y , x+width, y+height};

	int result = DrawText(consoleDC, string, length, &rect, DT_BOTTOM);

	if(result == 0)
	{
		std::cout << "Could not draw!";
	}
}

void ConsoleTextRenderer::nextLine()
{
	currentRow += lineHeight;
	currentCol = 0;

	SIZE textSize;
	int result = GetTextExtentPoint32( consoleDC, " ", 1, &textSize);
	lineHeight = textSize.cy;
}

void ConsoleTextRenderer::drawTextToCurrentLine(const char *text, int length)
{
	SIZE textSize;
	int result = GetTextExtentPoint32( consoleDC, text, length, &textSize);
	drawText(text, length, currentCol, currentRow, textSize.cx, textSize.cy);
	currentCol += textSize.cx;
	if(textSize.cy > lineHeight)
	{
		lineHeight = textSize.cy;
	}

}

