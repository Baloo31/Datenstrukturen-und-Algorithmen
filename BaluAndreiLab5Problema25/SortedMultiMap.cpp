#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Functie care verifica daca un numar este prim sau nu
bool isPrime(int n) {
	bool prime = true;
	if (n == 0 || n == 1) {
		prime = false;
	}
	else {
		for (int i = 2; i <= n / 2; ++i) {
			if (n % i == 0) {
				prime = false;
				break;
			}
		}
	}
	return prime;
}


/*
Constructor
best case: Theta(m); worst case: Theta(m); average case: Theta(m); general : Theta(m)
*/
SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->anzahlElemente = 0;
	this->belegungsfaktor = 0.0;
	this->kapazitat = 13;
	this->listen = new Node * [this->kapazitat];
	for (int index = 0; index < this->kapazitat; index++) {
		this->listen[index] = NULL;
	}
}

/*
best case: Theta(m); worst case: Theta(belegungsfaktor*m); average case: O(belegungsfaktor*m); general : Theta(belegungsfaktor*m)
*/
void SortedMultiMap::verkettung(SortedMultiMap other) {
	if (this->rel == other.rel) {
		// Parcurg toate elementele din SMM-ul primit ca parametru
		// Adaug cate un astfel de element in SMM-ul pentru care am apelat metoda
		// Simultan sterg acel element din SMM-ul primit ca parametru;
		for (int idx = 0; idx < other.kapazitat; idx++) {
			while (other.listen[idx] != NULL) {
				TKey key = other.listen[idx]->elem.first;
				TValue value = other.listen[idx]->elem.second;
				this->add(key, value);
				other.remove(key, value);
			}
		}
		// Schimbarile suferite de SMM-ul primit ca parametru nu vor fi salvate, deoarece am lucrat cu o copie a lui
	}
	else {
		throw exception();
	}
}


/*
Functia de hash
best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
*/
int SortedMultiMap::hashFunction(TKey key) const {
	if (key < 0) {
		key = -key;
	}
	return key % this->kapazitat;
}


/*
best case: Theta(n*m); worst case: Theta(belegungsfaktor*n*m); average case: O(belegungsfaktor*n*m); general : O(belegungsfaktor*n*m)
*/
void SortedMultiMap::reHash() {
	// Se creeaza un nou HT
	SortedMultiMap newHT = SortedMultiMap(this->rel);

	// Se alege noua capacitate

	newHT.kapazitat = 2 * this->kapazitat;
	while (!isPrime(newHT.kapazitat)) {
		newHT.kapazitat += 1;
	}
	delete[] newHT.listen;
	newHT.listen = new Node * [newHT.kapazitat];
	for (int idx = 0; idx < newHT.kapazitat; idx++) {
		newHT.listen[idx] = NULL;
	}


	// Transfer toate elementele in HT-ul nou pentru a se creea noile liste cu mai putine coliziuni
	// Ulterior dealoc array-ul de liste
	for (int idx = 0; idx < this->kapazitat; idx++) {
		while (this->listen[idx] != NULL) {
			TKey key = this->listen[idx]->elem.first;
			TValue value = this->listen[idx]->elem.second;
			newHT.add(key, value);
			this->remove(key, value);
		}
	}
	delete[] this->listen;

	// Dupa remove numarul de elemente din HT-ul initial a devenit 0
	// Capacitatea este actualizata
	this->kapazitat = newHT.kapazitat;

	// Ma pregatesc pentru aducere Elementelor inapoi in ordinea lor actuala
	this->listen = new Node * [this->kapazitat];
	for (int idx = 0; idx < this->kapazitat; idx++) {
		this->listen[idx] = NULL;
	}

	// Aduc pe rand fiecare element inapoi in HT-ul initial
	// Simultan eliberez HT-ul nou
	for (int idx = 0; idx < newHT.kapazitat; idx++) {
		while (newHT.listen[idx] != NULL) {
			TKey key = newHT.listen[idx]->elem.first;
			TValue value = newHT.listen[idx]->elem.second;
			this->add(key, value);
			newHT.remove(key, value);
		}
	}
	// Dealoc array-ul HT-ului nou
	delete[] newHT.listen;
}


/*
best case: Theta(1); worst case: Theta(n*m); average case: O(n) amortisiert;  general : O(n) amortisiert
*/
void SortedMultiMap::add(TKey c, TValue v) {

	// Daca am in medie mai mult de 2 Elemente in fiecare Lista din array, atunci este nevoie de rehash
	this->belegungsfaktor = double(this->anzahlElemente) / this->kapazitat;
	if (this->belegungsfaktor >= 2) {
		this->reHash();
	}

	int position = this->hashFunction(c);
	Node* newNode = new Node;
	newNode->elem.first = c;
	newNode->elem.second = v;

	// Adaugare cand lista e goala
	if (this->listen[position] == NULL){
		this->listen[position] = newNode;
		newNode->next = NULL;
	}
	else {
		Node* prevNode = NULL;
		Node* index = this->listen[position];
		// Cat timp mai am elemente in lista iar relatia este respectata
		while (index->next != NULL && this->rel(c, index->elem.first)) {
			prevNode = index;
			index = index->next;
		}

		// Adaugare la final (In cazul in care relatia este respectata)
		if (index->next == NULL && index != this->listen[position]) {
			index->next = newNode;
			newNode->next == NULL;
		}
		// Adaugare pe pozitia anterioara
		else {
			// In cazul primului element
			if (prevNode == NULL) {
				newNode->next = this->listen[position];
				this->listen[position] = newNode;
			}
			// In cazul ului element din interiorul listei
			else {
				newNode->next = index;
				prevNode->next = newNode;
			}
		}
	}
	this->anzahlElemente += 1;
}


/*
best case: Theta(1); worst case: Theta(n); average case: Theta(belegungsfaktor+1); general : O(belegungsfaktor+1)
*/
vector<TValue> SortedMultiMap::search(TKey c) const {

	int position = this->hashFunction(c);
	vector<TValue> values = {};

	Node* index = this->listen[position];
	// Parcurg toate Elementele pana cand relatia nu mai este respectata sau am ajuns la finalul listei
	while (index != NULL && this->rel(c, index->elem.first)) {
		if (index->elem.first == c) {
			// Adaug in rezultat doar elementele care au acea cheie
			values.push_back(index->elem.second);
		}
		index = index->next;
	}
	return values;
}


/*
best case: Theta(1); worst case: Theta(n); average case: Theta(belegungsfaktor+1); general : O(belegungsfaktor+1)
*/
bool SortedMultiMap::remove(TKey c, TValue v) {

	int position = this->hashFunction(c);
	Node* index = this->listen[position];

	// Daca lista e goala nu exista elementul
	if (index == NULL) {
		return false;
	}
	
	// Stergere de pe prima pozitie
	if (index->elem.first == c && index->elem.second == v) {
		this->listen[position] = index->next;
		delete index;
		this->anzahlElemente -= 1;
		return true;
	}

	// Stergere din interior / de la final
	Node* prevNode = NULL;
	while (index != NULL && this->rel(c, index->elem.first)) {
		if (c == index->elem.first && index->elem.second == v){
			prevNode->next = index->next;
			delete index;
			this->anzahlElemente -= 1;
			return true;
		}
		prevNode = index;
		index = index->next;
	}

	// Elementul cautat nu exista (S-a terminat lista sau am trecut de locul unde era asteptata cheia fiind sortat)
	return false;
}


/*
best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
*/
int SortedMultiMap::size() const {
	return this->anzahlElemente;
}


/*
best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
*/
bool SortedMultiMap::isEmpty() const {
	if (this->anzahlElemente == 0) return true;
	return false;
}


SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}


/*
best case: Theta(1); worst case: Theta(belegungsfaktor * m); average case: Theta(belegungsfaktor * m); general : Theta(belegungsfaktor * m)
*/
SortedMultiMap::~SortedMultiMap() {
	// Parcurg toate nodurile si le dealoc pe rand folosindu-ma de remove
	for (int idx = 0; idx < this->kapazitat; idx++) {
		while (this->listen[idx] != NULL) {
			TKey key = this->listen[idx]->elem.first;
			TValue value = this->listen[idx]->elem.second;
			this->remove(key, value);
		}
	}
	// Cand ajung aici stiu ca nu mai am elemente si pot dealoca si array-ul
	delete[] this->listen;
}