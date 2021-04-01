#include <exception>
#include "RandomAccessIterator.h"
#include "Bag.h"

using namespace std;

RandomAccessIterator::RandomAccessIterator(const Bag& c, int position) : bag(c)
{
	// index-ul nu poate fi initial mai mare sau egal cu size-ul bag-ului (nici negativ), in acesc caz va aparea o exceptie
	if ((position >= 0) && (position < bag.size())) {
		this->index = position;
	}
	else throw exception();
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void RandomAccessIterator::first() {
	// Index 0 are sens doar daca Bag-ul nu este gol
	if (this->bag.size() != 0) {
		this->index = 0;
	}
	else {
		throw exception();
	}
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void RandomAccessIterator::next(int steps) {
	if (valid() && (steps > 0)) {
		this->index += steps;
	}
	else {
		throw exception();
	}
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void RandomAccessIterator::prev(int steps) {
	if (valid() && (steps > 0)) {
		this->index -= steps;
	}
	else {
		throw exception();
	}
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
bool RandomAccessIterator::valid() const {
	if (this->index < this->bag.size()) {
		return true;
	}
	return false;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
TElem RandomAccessIterator::getCurrent() const
{
	// Pentru a returna elementul de tip TElem din u trebuie sa ne aflam pe o pozitie valida
	if (valid()) {
		// Aflam indexul din u cu ajutorul valorii din p
		int positionInU = this->bag.pElements[this->index];
		return this->bag.uElements[positionInU]; // Returnam elementul curent
	}
	else {
		throw exception();
	}
}