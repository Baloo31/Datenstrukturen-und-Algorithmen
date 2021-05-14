#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	this->listPosition = 0; 
	// Caut pozitia primei liste care nu e goala cat timp nu depasesc capacitatea array-ului de headuri
	while ((this->listPosition < this->map.kapazitat) && (this->map.listen[listPosition] == NULL)) {
		this->listPosition += 1;
	}
	if (this->listPosition < this->map.kapazitat) {
		// Daca am ajuns aici stiu sigur ca am gasit un element si pot arata spre el
		this->listElement = this->map.listen[listPosition];
	} 
	// Daca nu sunt elemente arat spre un element null
	else {
		this->listElement = NULL;
	}
}

void SMMIterator::first() {
	this->listPosition = 0;
	// Caut pozitia primei liste care nu e goala cat timp nu depasesc capacitatea array-ului de headuri
	while ((this->listPosition < this->map.kapazitat) && (this->map.listen[listPosition] == NULL)) {
		this->listPosition += 1;
	}

	if (this->listPosition < this->map.kapazitat) {
		this->listElement = this->map.listen[listPosition];
	}
	// Daca nu sunt elemente
	else {
		this->listElement = NULL;
	}
}



void SMMIterator::next() {
	if (this->valid()) {
		if (this->listElement->next != NULL) {
			this->listElement = this->listElement->next;
		}
		else {
			this->listPosition += 1;
			// Parcurga pana gasesc o lista ce contine elemente (daca mai am vreuna)
			while ((this->listPosition < this->map.kapazitat) && (this->map.listen[listPosition] == NULL)) {
				this->listPosition += 1;
			}
			if (this->listPosition < this->map.kapazitat) {
				this->listElement = this->map.listen[this->listPosition];
			}
			else {
				this->listElement = NULL;
			}
		}
	}
	else {
		throw exception();
	}
}


/*
best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
*/
bool SMMIterator::valid() const {
	// Daca pozitia pe care ma aflu nu arata catre o lista goala iar capacitatea nu este  depasita atunci ma aflu pe o pozitie valida
	if (this->listPosition < this->map.kapazitat && this->listElement != NULL) {
		return true;
	}
	return false;
}


/*
best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
*/
TElem SMMIterator::getCurrent() const {
	// Daca ma aflu pe o pozitie valida este returnat elementul de pe pozitia aceea
	if (this->valid()) {
		return this->listElement->elem;
	}
	// Altfel este aruncata o exceptie
	else {
		throw exception();
	}
}