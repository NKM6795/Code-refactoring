#include "SinglyLinked.h"

SinglyLinked::SinglyLinked()
{
	length = 0;
}

void SinglyLinked::pushBack(int i, int j)
{
	SinglyNode *newNode = new SinglyNode(i, j);
	if (length == 0)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	++length;
}

void SinglyLinked::popFront()
{
	if (length != 0)
	{
		SinglyNode *node = head;
		head = head->next;
		delete node;
		--length;
	}
}

void SinglyLinked::clear()
{
	while (length > 0)
	{
		popFront();
	}
}

int SinglyLinked::getSize()
{
	return length;
}

SinglyNode *SinglyLinked::getHead()
{
	return head;
}


