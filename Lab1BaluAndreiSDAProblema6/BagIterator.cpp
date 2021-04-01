#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	this->index = 0;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void BagIterator::first() {
	if (this->bag.size() != 0) {
		this->index = 0;
	}
	else {
		throw exception();
	}
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void BagIterator::next() {
	if (valid()) {
		this->index++;
	}
	else {
		throw exception();
	}
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
bool BagIterator::valid() const {
	if (this->index < this->bag.size()) {
		return true;
	}
	return false;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
TElem BagIterator::getCurrent() const
{
	if (valid()) {
		int positionInU = this->bag.pElements[this->index]; // Elementul de pe pozitia indexului curent din p este pozitia elementului pe care il dorim din u
		return this->bag.uElements[positionInU]; // Accesarea elementului de tip TElem
	}
	else {
		throw exception();
	}
}