//
// Created by frede on 2017-10-01.
//

#include "TextTree.h"

void TextTree::traverse()
{
	root.traverse();
}

TextTree::TextTree(std::string &string) : root(nullptr, string)
{
	root.setCursorPos(0);
	root.split();
}

void TextTree::moveCursorRight()
{
	Node *cursorNode = getCursorNode();
	cursorNode->setCursorPos(cursorNode->getCursorPos() + 1);
}

void TextTree::moveCursorLeft()
{
	Node *cursorNode = getCursorNode();
	cursorNode->setCursorPos(cursorNode->getCursorPos() - 1);
}

Node *TextTree::getCursorNode()
{
	Node *currentNode = &root;
	while (currentNode->getCursorPos() < 0)
	{

		int direction = currentNode->getCursorDirection();
		if (direction == -1)
		{
			currentNode = currentNode->getLeft();
		} else if (direction == 1)
		{
			currentNode = currentNode->getRight();
		} else
		{
			break;
		}
	}
	return currentNode;
}

