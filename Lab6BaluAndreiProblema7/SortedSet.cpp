#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->rel = r;
	this->root = NULL;
	this->nrElements = 0;
}


/*
best case: Theta(1)
worst case: Theta(h)
average case: Theta(h)
general: O(h) ~ O(n)
*/
bool SortedSet::add(TComp elem) {
	// Adaug doar daca elementul nu este deja in container
	if (this->search(elem)) {
		return false;
	}

	this->root = insert_rec(this->root, elem, this->rel);
	this->nrElements++;
	return true;
}


/*
best case: Theta(1)
worst case: Theta(h)
average case: Theta(h)
general: O(h) ~ O(n)
*/
BSTNode* insert_rec(BSTNode* node, TComp elem, Relation rel) {
	if (node == NULL) {
		// Se creeaza nodul pentru elementul ce trebuie adaugat
		// Am garantia ca ma aflu pe poitia unde trebuie sa il adaug
		node = new BSTNode;
		node->info = elem;
		node->left = NULL;
		node->right = NULL;
	}
	// In cazul in care nu se afla pe pozitia buna 
	// se petrece cautarea pozitiei pentru adaugare la standa / la dreapta conform relatiei
	else if (!rel(node->info, elem)) {
		node->left = insert_rec(node->left, elem, rel);
	}
	else {
		node->right = insert_rec(node->right, elem, rel);
	}
	return node;
}


/*
best case: Theta(1)
worst case: Theta(h)
average case: Theta(h)
general: O(h) ~ O(n)
*/
bool SortedSet::remove(TComp elem) {
	if (!this->search(elem)) {
		return false;
	}
    this->root = remove_rec(this->root, elem, rel);
	this->nrElements--;
	return true;
}


/*
best case: Theta(1)
worst case: Theta(h)
average case: Theta(h)
general: O(h) ~ O(n)
*/
BSTNode* remove_rec(BSTNode* node, TComp elem, Relation rel) {
	// Daca ma aflu pe o legatura ce nu duce catre un element (Valabil si daca containerul e gol)
	if (node == NULL) {
		return NULL;
	}
	// Daca ma aflu pe elementul ce trebuie sters (3 cazuri)
	else if (node->info == elem) {
		// Daca nodul este o frunza poate sa fie dealocat direct
		if (node->left == NULL && node->right == NULL) {
			delete node;
			return NULL;
		}
		// Daca are doar un succesor este inlocuit cu acesta
		// urmand ca acesta sa fie sters
		else if (node->left == NULL) {
			return node->right;
		}
		else if (node->right == NULL) {
			return node->left;
		}
		// Daca nodul are doi succesori se stabileste minimul din partea dreapta a subarborelui si se inlocuieste cu acesta
		// urmand ca acesta sa fie sters
		else {
			BSTNode* min = minimum(node->right);
			node->info = min->info;
			node->right = remove_rec(node->right, min->info, rel);
			return node;
		}
	}
	// Altfel, nu ma aflu pe nodul care trebuie sters si contiui sa il caut in raport cu relatia
	else if (!rel(node->info, elem)) {
		node->left = remove_rec(node->left, elem, rel);
		return node;
	} else if (rel(node->info, elem)) {
		node->right = remove_rec(node->right, elem, rel);
		return node;
	}
}


/*
best case: Theta(1)
worst case: Theta(n)
average case: Theta(n)
general: O(n)
*/
BSTNode* minimum(BSTNode* node){
	// Pentru a afla minimul este necesara deplasarea pana la frunza cea mai din stanga
	BSTNode* currentNode = node;
	if (currentNode == NULL) {
		return NULL;
	}
	else {
		while (currentNode->left != NULL) {
			currentNode = currentNode->left;
		}
		return currentNode;
	}
}


/*
best case: Theta(1)
worst case: Theta(h)
average case: Theta(h)
general: O(h) ~ O(n)
*/
bool SortedSet::search(TComp elem) const {
	return search_rec(this->root, elem, this->rel);
}

bool search_rec(BSTNode* node, TComp& elem, Relation rel){
	// Conditia de oprire pentru cautare: Pozitia pe care am ajuns nu se afla in arbore
	if (node == NULL) {
		return false;
	}
	else {
		// Daca ma aflu pe nodul pe care il caut ma opresc
		if (node->info == elem) {
			return true;
		}
		// Continui cautarea in raport cu relatia (la stanga sau dreapta)
		else if (!rel(node->info, elem)) {
			return search_rec(node->left, elem, rel);
		}
		return search_rec(node->right, elem, rel);
	}
}


/*
best case: Theta(1)
worst case: Theta(1)
average case: Theta(1)
general: Theta(1)
*/
int SortedSet::size() const {
	return this->nrElements;
}


/*
best case: Theta(1)
worst case: Theta(1)
average case: Theta(1)
general: Theta(1)
*/
bool SortedSet::isEmpty() const {
	if (this->root == NULL) {
		return true;
	}
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


/*
best case: Theta(n)
worst case: Theta(n)
average case: Theta(n)
general: Theta(n)
*/
SortedSet::~SortedSet() {
	TComp elToRemove;
	// Daca am elemente in arbore sterg pas cu pas radacina pana acesta devine gol
	while (!this->isEmpty()) {
		elToRemove = this->root->info;
		this->remove(elToRemove);
	}
}

