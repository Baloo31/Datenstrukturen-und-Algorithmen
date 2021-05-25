#pragma once
#include "SortedSet.h"
#include "Stack.h"
using namespace std;


//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	Stack<BSTNode*> stack;
	BSTNode* currentNode;

public:
	void first();
	void last();
	void next();
	void prev();
	TElem getCurrent();
	bool valid() const;
};
