//
// Created by frede on 2017-10-01.
//

#include <iostream>
#include "Node.h"

void Node::split()
{
	int length = value.size();


	int splitIndex = getBestSplitIndex(value);
	if (splitIndex != -1)
	{
		std::string left = value.substr(0, splitIndex);
		std::string right = value.substr(splitIndex + 1, length);

		setLeft(new Node(this, left));
		setRight(new Node(this, right));

		std::string newValue;
		newValue.push_back(value[splitIndex]);
		setValue(newValue);

		if (cursorPos >= 0)
		{
			if (cursorPos < splitIndex)
			{
				getLeft()->setCursorPos(cursorPos);
				cursorPos = -1;
				cursorDirection = -1;
			} else if (cursorPos > splitIndex)
			{
				getRight()->setCursorPos(cursorPos - splitIndex - 1);
				cursorPos = -1;
				cursorDirection = 1;
			} else
			{
				cursorPos = 0;
			}
		}

		getLeft()->split();
		getRight()->split();
	}
}

int Node::getBestSplitIndex(std::string str)
{
	int middleIndex = str.length() / 2;
	for (int i = 0; i < middleIndex; i++)
	{
		if (shouldSplit(str[middleIndex - i]))
		{
			return middleIndex - i;
		}

		if (shouldSplit(str[middleIndex + i]))
		{
			return middleIndex + i;
		}
	}

	return -1;
}

bool Node::shouldSplit(char c)
{
	return c == ' ' || c == '\n';
}

void Node::traverse(const std::function<void (Node*)>& doFunction)
{
	if (getLeft() != nullptr)
	{
		getLeft()->traverse(doFunction);
	}

	doFunction(this);

	if (getRight() != nullptr)
	{
		getRight()->traverse(doFunction);
	}

}

int Node::getCursorPos() const
{
	return cursorPos;
}

void Node::setCursorPos(int newCursorPos)
{
	int vLength = value.length();
	if (newCursorPos >= vLength)
	{
		cursorPos = -1;
		if (right != nullptr)
		{
			right->setCursorPosToStart();
			cursorDirection = 1;
			return;
		}

		if (parent != nullptr)
		{
			parent->moveCursorForwardsInChild(this);
		}
	}
	else if(newCursorPos < 0)
	{
		cursorPos = -1;
		if(left != nullptr)
		{
			left->setCursorPosToEnd();
			cursorDirection = -1;
			return;
		}

		if(parent != nullptr)
		{
			parent->moveCursorBackwardsInChild(this);
		}
	}
	else
	{
		if (value[newCursorPos] == '\n')
		{
			if (newCursorPos > cursorPos)
			{
				setCursorPos(newCursorPos + 1);
			} else
			{
				setCursorPos(newCursorPos - 2);
			}
		} else
		{
			cursorPos = newCursorPos;
		}
	}
}

int Node::getCursorDirection() const
{
	return cursorDirection;
}

void Node::setCursorDirection(int cursorDirection)
{
	Node::cursorDirection = cursorDirection;
}

void Node::setCursorPosToStart()
{
	if (left != nullptr)
	{
		cursorDirection = -1;
		left->setCursorPosToStart();
	}
	else if(value.length() > 0)
	{
		cursorPos = 0;
		cursorDirection = 0;
	}
	else if (right != nullptr)
	{
		cursorDirection = 1;
		right->setCursorPosToStart();
	}

}

void Node::setCursorPosToEnd()
{
	if(right != nullptr)
	{
		cursorDirection = 1;
		right->setCursorPosToEnd();
	}
	else if(value.length() > 0)
	{
		cursorPos = value.length()-1;
		cursorDirection = 0;
	}
	else if(left != nullptr)
	{
		cursorDirection = -1;
		left->setCursorPosToEnd();
	}
}
void Node::moveCursorForwardsInChild(Node *origin)
{
	if (origin == left)
	{
		setCursorPos(0);
	}
	else
	{
		if(parent != nullptr)
		{
			parent->moveCursorForwardsInChild(this);
		}
	}
}

void Node::moveCursorBackwardsInChild(Node *origin)
{
	if(origin == right)
	{
		setCursorPos(0);
	}
	else
	{
		if(parent != nullptr)
		{
			parent->moveCursorBackwardsInChild(this);
		}
	}
}



