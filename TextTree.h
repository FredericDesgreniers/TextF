//
// Created by frede on 2017-10-01.
//

#pragma once


#include "Node.h"

class TextTree
{
	Node root;
public:
	TextTree(std::string &string);

	void traverse(std::function<void (Node*)> doFunction);

	Node *getCursorNode();

	void moveCursorRight();
	void moveCursorLeft();
};

