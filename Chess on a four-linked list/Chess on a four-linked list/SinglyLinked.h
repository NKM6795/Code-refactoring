#include "BasicElement.h"

class SinglyLinked
{
private:
	SinglyNode *head = nullptr;
	SinglyNode *tail = nullptr;
	int length;

public:
	SinglyLinked();
	void pushBack(int i, int j);
	void popFront();
	void clear();
	int getSize();
	SinglyNode *getHead();
};