//
// Created by frede on 2017-10-01.
//

#pragma once
#include <string>
#include "TextRenderer.h"
#include <functional>
class Node
{
	std::string value;
	Node *left = nullptr;
	Node *right = nullptr;
	Node *parent = nullptr;

	int cursorPos = -1;

	int cursorDirection = 0;
public:
	int getCursorDirection() const;

	void setCursorDirection(int cursorDirection);

public:
	int getCursorPos() const;

	void setCursorPos(int cursorPos);

	void setCursorPosToStart();

	void setCursorPosToEnd();

	void moveCursorForwardsInChild(Node *origin);
	void moveCursorBackwardsInChild(Node *origin);
public:
	Node(Node *parent, std::string text): parent(parent), value(text)
	{

	}

	void split();

	int getBestSplitIndex(std::string str);

	bool shouldSplit(char c);

	void traverse(const std::function<void (Node*)>& f);

	Node *getLeft() const
	{
		return left;
	}

	void setLeft(Node *left)
	{
		Node::left = left;
	}

	Node *getRight() const
	{
		return right;
	}

	void setRight(Node *right)
	{
		Node::right = right;
	}

	std::string getValue()
	{
		return value;
	}

	void setValue(std::string value)
	{
		Node::value = value;
	}
};


