#include "Bag.h"

class RandomAccessIterator
{
	friend class Bag;

private:
	const Bag& bag;
	int index;

	RandomAccessIterator(const Bag& c, int position);
public:
	void first();
	void next(int steps);
	void prev(int steps);
	TElem getCurrent() const;
	bool valid() const;
};
