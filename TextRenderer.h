//
// Created by frede on 2017-10-02.
//

#pragma once

class TextRenderer
{
public:
	TextRenderer();

	virtual void drawText(const char* string, int length, int x, int y, int width, int height)
	{

	}
	virtual void nextLine()
	{

	}
};