#include "Bag.h"
#include "BagIterator.h"
#include "RandomAccessIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->uCapacity = 4;
	this->uNrElements = 0;
	this->uElements = new TElem[uCapacity];

	this->pCapacity = 4;
	this->pNrElements = 0;
	this->pElements = new int[pCapacity];
}


// best case: Theta(1); worst case: Theta(n); average case: O(n); general : O(n)
void Bag::add(TElem elem) {
	bool alreadyExists = false; int position;
	// Se stabileste daca elementul ce urmeaza sa fie adaugat exista deja, iar daca exista obtinem si indexul sau
	for (int index = 0; index < this->uNrElements; index++) {
		if (elem == this->uElements[index]) {
			alreadyExists = true;
			position = index;
			break;
		}
	}

	if (!alreadyExists) {
		// Daca elementul adaugat nu este unic trebuie sa adaugat atat in u cat si in p
		if (this->uCapacity == this->uNrElements) {
			this->uCapacity *= 2;
			TElem* newArray = new TElem[this->uCapacity];
			for (int index = 0; index < this->uNrElements; index++) {
				newArray[index] = this->uElements[index];
			}
			delete[] this->uElements;
			this->uElements = newArray;
		}

		this->uElements[this->uNrElements] = elem;
		this->uNrElements++;

		if (this->pCapacity == this->pNrElements) {
			this->pCapacity *= 2;
			int* newArray = new int[this->pCapacity];
			for (int index = 0; index < this->pNrElements; index++) {
				newArray[index] = this->pElements[index];
			}
			delete[] this->pElements;
			this->pElements = newArray;
		}

		this->pElements[this->pNrElements] = this->uNrElements - 1;
		this->pNrElements++;
	}
	else {
		// Daca elementul exista deja in u, acesta va fi adaugat doar in p
		if (this->pCapacity == this->pNrElements) {
			this->pCapacity *= 2;
			int* newArray = new int[this->pCapacity];
			for (int index = 0; index < this->pNrElements; index++) {
				newArray[index] = this->pElements[index];
			}
			delete[] this->pElements;
			this->pElements = newArray;
		}

		this->pElements[this->pNrElements] = position;
		this->pNrElements++;
	}
}


// best case: Theta(n); worst case: Theta(n); average case: Theta(n); general : Theta(n)
bool Bag::remove(TElem elem) {
	int position{ -1 };
	// Cautarea pozitiei elementului (in cazul in care exista)
	for (int index = 0; index < uNrElements; index++) {
		if (elem == this->uElements[index]) {
			position = index;
		}
	}
	// Daca e goala / nu s-a gasit elementul dorit nu se poate sterge
	if (position == -1) {
		return false;
	}

	// Avand garantia ca exista cel putin unul, se stabileste numarul de aparitii si se retine pozitia ultimei aparitii
	int countOccurrences{ 0 };
	int lastOccurrence{ -1 };
	for (int index = 0; index < pNrElements; index++) {
		if (position == this->pElements[index]) {
			countOccurrences++;
			lastOccurrence = index;
		}
	}

	// Daca elementul apare o singura data, acesta trebuie eliminat si din p si din u
	if (countOccurrences == 1) {
		// Stergere din u
		this->uElements[position] = this->uElements[this->uNrElements - 1];
		this->uNrElements--;
		for (int index = 0; index < this->pNrElements; index++) {
			if (this->pElements[index] == uNrElements) {
				this->pElements[index] = position;
			}
		}
	}
	// Altfel, este eliminat doar din p
	this->pElements[lastOccurrence] = this->pElements[this->pNrElements - 1];
	this->pNrElements--;


	//Dealocare in u
	if ((this->uNrElements != 0) && (this->uCapacity >= this->uNrElements * 3)) {
		this->uCapacity /= 2;
		TElem* newArray = new TElem[this->uCapacity];
		for (int index = 0; index < this->uNrElements; index++) {
			newArray[index] = this->uElements[index];
		}
		delete[] this->uElements;
		this->uElements = newArray;
	}

	//Dealocare in p
	if ((this->pNrElements != 0) && (this->pCapacity >= this->pNrElements * 3)) {
		this->pCapacity /= 2;
		int* newArray = new int[this->pCapacity];
		for (int index = 0; index < this->pNrElements; index++) {
			newArray[index] = this->pElements[index];
		}
		delete[] this->pElements;
		this->pElements = newArray;
	}

	return true;
}


// best case: Theta(1); worst case: Theta(n); average case: Theta(n); general : O(n)
bool Bag::search(TElem elem) const {
	for (int index = 0; index < this->uNrElements; index++) {
		if (this->uElements[index] == elem) {
			return true;
		}
	}
	return false;
}


// best case: Theta(n); worst case: Theta(n); average case: Theta(n); general : Theta(n)
int Bag::nrOccurrences(TElem elem) const {
	int elemOccurrences{ 0 };
	int position{ -1 };
	// Cautam in u sa vedem daca exista elementul in Bag si ii aflam astfel si index-ul sau
	for (int index = 0; index < this->uNrElements; index++) {
		if (elem == this->uElements[index]) {
			position = index;
			break;
		}
	}
	// Stiind index-ul din u putem stabili parcurgand complet p numarul de aparitii al elementului
	if (position != -1) {
		for (int index = 0; index < this->pNrElements; index++) {
			if (position == this->pElements[index]) {
				elemOccurrences++;
			}
		}
	}
	else {
		return 0;
	}
	return elemOccurrences;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
int Bag::size() const {
	return this->pNrElements;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
bool Bag::isEmpty() const {
	if ((this->pNrElements == 0) && (this->uNrElements == 0)) {
		return true;
	}
	return false;
}


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


// Returneaza un random access iterator pentru Bag
RandomAccessIterator Bag::iteratorRandom(int position) const {
	return RandomAccessIterator(*this, position);
}


Bag::~Bag() {
	delete[] this->uElements;
	delete[] this->pElements;
}
