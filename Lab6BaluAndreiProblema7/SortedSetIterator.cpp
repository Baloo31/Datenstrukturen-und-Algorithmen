#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->stack = Stack<BSTNode*>();
	this->currentNode = multime.root;
	// Deplasarea spre cel mai mic element din punct de vedere al relatiei
	while (this->currentNode != NULL) {
		stack.push(this->currentNode);
		this->currentNode = this->currentNode->left;
	}
	if (!stack.isEmpty()) {
		this->currentNode = stack.top();
	}
	else {
		this->currentNode = NULL;
	}
}


// best case: Theta(1); worst case: Theta(n); average case: Theta(n); general: O(n)
void SortedSetIterator::first() {
	this->stack = Stack<BSTNode*>();
	this->currentNode = multime.root;
	// Deplasarea spre cel mai mic element din punct de vedere al relatiei
	while (this->currentNode != NULL) {
		stack.push(this->currentNode);
		this->currentNode = this->currentNode->left;
	}
	// Nodul curent este ultimul adaugat pe stiva (cel mai mic), iar in cazul in care stiva e goala returnez null
	if (!stack.isEmpty()) {
		this->currentNode = stack.top();
	}
	else {
		this->currentNode = NULL;
	}
}


// best case: Theta(1); worst case: Theta(n); average case: Theta(n); general: O(n)
void SortedSetIterator::last() {
	this->stack = Stack<BSTNode*>();
	this->currentNode = multime.root;
	// Deplasarea spre cel mai mare element din punct de vedere al relatiei
	while (this->currentNode != NULL) {
		stack.push(this->currentNode);
		this->currentNode = this->currentNode->right;
	}
	// Nodul curent este ultimul adaugat pe stiva (cel mai mare), iar in cazul in care stiva e goala returnez null
	if (!stack.isEmpty()) {
		this->currentNode = stack.top();
	}
	else {
		this->currentNode = NULL;
	}
}


// best case: Theta(1); worst case: Theta(n); average case: Theta(n); general: O(n)
void SortedSetIterator::next() {
	// Exceptie daca nu ma aflu pe o pozitie valida
	if (this->valid()) {
		// Scot adresa unui nod din stiva si il vizitez
		this->currentNode = stack.pop();
		if (this->currentNode != NULL) {
			// Ma deplasez spre elementul din dreapta sa
			this->currentNode = this->currentNode->right;
			while (this->currentNode != NULL) {
				// Pun pe stiva nodul si ma deplases pe cel din stanga lui pana nu mai are succesor in stanga
				this->stack.push(this->currentNode);
				this->currentNode = this->currentNode->left;
			}
		}
		if (!this->stack.isEmpty()) {
			this->currentNode = this->stack.top();
		}
		else {
			this->currentNode = NULL;
		}
	}
	else throw exception();
}


// best case: Theta(1); worst case: Theta(n); average case: Theta(n); general: O(n)
void SortedSetIterator::prev() {
	// Exceptie daca nu ma aflu pe o pozitie valida
	if (this->valid()) {
		// Scot adresa unui nod din stiva si il vizitez
		this->currentNode = stack.pop();
		if (this->currentNode != NULL) {
			// Ma deplasez spre elementul din stanga sa
			this->currentNode = this->currentNode->left;
			while (this->currentNode != NULL) {
				// Pun pe stiva nodul si ma deplases pe cel din stanga lui pana nu mai are succesor in stanga
				this->stack.push(this->currentNode);
				this->currentNode = this->currentNode->right;
			}
		}
		if (!this->stack.isEmpty()) {
			this->currentNode = this->stack.top();
		}
		else {
			this->currentNode = NULL;
		}
	}
	else throw exception();
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (this->valid()) {
		return this->currentNode->info;
	}
	throw exception();
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
bool SortedSetIterator::valid() const {
	if (this->currentNode == NULL) {
		return false;
	}
	return true;
}
