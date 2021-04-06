#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

Queue::Queue() {
	this->head = NULL;
	this->tail = NULL;
}

// Best case: Theta(1); Worst case: Theta(1); Average case: Theta(1); General: Theta(1);
void Queue::push(TElem elem) {
	// Vorbereiten des Knotens geschiet in beide Falle
	Node* newNode = new Node;
	newNode->value = elem;
	newNode->next = NULL;

	// Einfugen falls Queue leer ist
	if (this->head == NULL) {
		newNode->prev = NULL;
		this->tail = newNode;
		this->head = newNode;
	}
	// Einfugen am Ende
	else {
		newNode->prev = this->tail;
		this->tail->next = newNode;
		this->tail = newNode;
	}
}

// Best case: Theta(1); Worst case: Theta(1); Average case: Theta(1); General: Theta(1);
TElem Queue::top() const {
	if (this->head != NULL) {
		return this->head->value;
	}
	throw exception();
}

// Best case: Theta(1); Worst case: Theta(1); Average case: Theta(1); General: Theta(1);
TElem Queue::pop() {
	if (this->head == NULL) {
		throw exception();
	}

	TElem value = this->head->value;
	
	if (!((this->head->next == NULL) && (this->head->prev == NULL))) {
		Node* nodeToRemove = this->head;
		this->head = nodeToRemove->next;
		this->head->prev = NULL;
		delete nodeToRemove;
		return value;
	}

	delete head;
	this->head = NULL;
	this->tail = NULL;
	return value;
}

// Best case: Theta(1); Worst case: Theta(1); Average case: Theta(1); General: Theta(1);
bool Queue::isEmpty() const {
	if (this->head == NULL) {
		return true;
	}
	return false;
}

Queue::~Queue() {
	while (this->head != NULL) {
		this->pop();
	}
}