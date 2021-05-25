#pragma once
#include <exception>
#include <utility>
using namespace std;

template <class Object>
struct StackNode{
	Object info;
	StackNode* next;
	StackNode* prev;
};

template <class Object>
class Stack
{
private:
	StackNode<Object>* head;
	StackNode<Object>* tail;
	int nrElements;

public:
	Stack() {
		this->head = NULL;
		this->tail = NULL;
		this->nrElements = 0;
	}

	// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
	void push(Object element) {
		StackNode<Object>* newNode = new StackNode<Object>;
		newNode->info = element;

		// Adaugare daca lista e goala
		if (this->isEmpty()) {
			this->head = newNode;
			this->tail = newNode;
			newNode->prev = NULL;
			newNode->next = NULL;
		}
		// Adaugare la finalul listei
		else {
			this->tail->next = newNode;
			newNode->prev = this->tail;
			this->tail = newNode;
			newNode->next = NULL;
		}
		this->nrElements++;
	}

	// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
	Object pop() {
		// Eceptie daca apelez stergerea cand lista e goala
		if (!this->isEmpty()) {
			// Elementul scos din lista va fi returnat de metoda
			Object valueToReturn = this->tail->info;
			
			// Stergere daca am un singur element in lista
			if (this->head == this->tail) {
				delete this->tail;
				this->head = NULL;
				this->tail = NULL;
			}
			// Stergerea ultimului element 
			else {
				this->tail = this->tail->prev;
				delete this->tail->next;
			}

			this->nrElements--;
			return valueToReturn;
		} 
		throw exception();
	}

	// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
	Object top() const {
		if (!this->isEmpty()) {
			return this->tail->info;
		}
		throw exception();
	}

	// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
	int size() const {
		return this->nrElements;
	}

	// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general: Theta(1)
	bool isEmpty() const {
		if (this->size() == 0) {
			return true;
		}
		return false;
	}

	// best case: Theta(n); worst case: Theta(n); average case: Theta(n); general: Theta(n)
	~Stack() {
		// Dealoc ultimul element pana cand lista devine goala
		while (!this->isEmpty()) {
			this->pop();
		}
	}
};
