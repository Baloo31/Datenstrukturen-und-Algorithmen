#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>
using namespace std;

MatrixIterator Matrix::iterator() const {
	return MatrixIterator(*this);
}


/*
Pre: Zwei Zellen der Matrix
Pos:
Vergleicht zwei Zellen aus der Matrix
Venn Zelle a lexikographisch vor Zelle b ist,
Dann ergibt die funktion true, sonst ergibt sie false
*/
bool isLess(const Tuple& a, const Tuple& b) {
	if (a.row < b.row) {
		return true;
	}
	if (a.row == b.row && a.column < b.column) {
		return true;
	}
	return false;
}


/*
Constructor
*/
Matrix::Matrix(int nrLines, int nrCols) {
	if (nrLines > 0 && nrCols > 0) {
		this->nrLin = nrLines;
		this->nrCol = nrCols;
		this->capacity = 4;
		this->nrElements = 0;

		this->elements = new Tuple[this->capacity];

		this->next = new int[this->capacity];
		for (int index = 0; index < this->capacity - 1; index++) {
			this->next[index] = index + 1;
		}
		this->next[this->capacity - 1] = -1;

		this->head = -1;
		this->firstEmpty = 0;
	}
	else throw exception();
}


/*
Pre: Eine Matrix
Post: Ergibt die Anzahl der Zeilen der Matrix
Komplexitat: -> best case: Theta(1); worst case: Theta(1); average case: Thera(1); general : Theta(1)
*/
int Matrix::nrLines() const {
	return this->nrLin;
}


/*
Pre: Eine Matrix
Post: Ergibt die Anzahl der Spalten der Matrix
Komplexitat: -> best case: Theta(1); worst case: Theta(1); average case: Thera(1); general : Theta(1)
*/
int Matrix::nrColumns() const {
	return this->nrCol;
}


/*
Pre: Eine Matrix und zwei koordinaten i und j
Pos: True wenn die Position (i,j) gultig ist
	 False wenn sie nicht gultig ist
Komplexitat: -> best case: Theta(1); worst case: Theta(1); average case: Thera(1); general : Theta(1)
*/
bool Matrix::validPosition(int i, int j) const {
	if (i >= 0 && i < this->nrLines() && j >= 0 && j < this->nrColumns()) {
		return true;
	}
	return false;
}


/*
Pre: Eine Matrix und zwei koordinaten i und j
Pos: Die Wert die in Matrix auf die Zeile i und Spalte j liegt
throws: exception falls Position (i,j) ungultig ist
Komplexitat: -> best case: Theta(1); worst case: Theta(n); average case: O(n); general : O(n)
*/
TElem Matrix::element(int i, int j) const {
	if (this->validPosition(i, j)) {
		int index = this->head;
		while (index != -1) {
			if (this->elements[index].row == i && this->elements[index].column == j) {
				return this->elements[index].value;
			}
			index = this->next[index];
		}
		return NULL_TELEM;
	}
	throw exception();
}


/*
Pre: Eine Matrix, eine Zeile, eine Spalte und ein Wert
Pos: Verandert die Wert der Zelle(i,j) in die Matrix und gibt das alte Wert zuruck
throws: exception falls Position (i,j) ungultig ist
Komplexitat: -> best case: Theta(1); worst case: Theta(n); average case: O(n); general : O(n) amortisiertS
*/
TElem Matrix::modify(int i, int j, TElem e) {
	// Position(i,j) soll valid sein
	if (this->validPosition(i, j)) {

		// Man durchquert die Zellen die ein Wert != 0 haben 
		int index = this->head;
		int prevNode = -1;
		while (index != -1) {
			if (this->elements[index].row == i && this->elements[index].column == j) {
				if (e == NULL_TELEM) {

					// Die alte Wert wird zuruckgegeben
					// Weil die neue Wert NULL ist, wird die gefundene Zelle aus dem Array entfernt
					TElem oldValue = this->elements[index].value;
					if (index == this->head) {
						this->head = this->next[this->head];
					}
					else {
						this->next[prevNode] = this->next[index];
					}
					this->next[index] = this->firstEmpty;
					this->firstEmpty = index;
					this->nrElements--;
					return oldValue;

				}
				else {

					// Die Wert der Zelle wird mit dem neuen Wert ersetzt und zuruckgegeben
					TElem oldValue = this->elements[index].value;
					this->elements[index].value = e;
					return oldValue;

				}
			}
			prevNode = index;
			index = this->next[index];
		}

		// Wenn das Element nicht gefunden war und die neue Wert ist NULL
		// dann bleibt das Array unverandert und wird die alte Wert(also auch NULL) zuruckgegeben
		if (e == NULL_TELEM) {
			return NULL_TELEM;
		}

		// Hier angekommen weiss man genau dass man eine Zelle einfugen mochte
		// Erstens geschiet es einem resize falls es notig ist
		if (this->firstEmpty == -1) {
			this->firstEmpty = this->capacity;

			// Capacity wird verdoppelt
			this->capacity = this->capacity * 2;

			// Die neue Arrays werden generiert und die Werten der alten Arrays werden hier kopiert
			Tuple* newElems = new Tuple[this->capacity];
			int* newNext = new int[this->capacity];
			for (int index = 0; index < this->nrElements; index++) {
				newElems[index] = this->elements[index];
				newNext[index] = this->next[index];
			}

			// Die Werte der alten Arrays werden dealoziert und mit dem neuen Arrays ersetzt
			delete[] this->elements;
			delete[] this->next;
			this->elements = newElems;

			// EmptyElements-Liste wird generiert
			for (int index = this->firstEmpty; index < this->capacity - 1; index++) {
				newNext[index] = index + 1;
			}
			newNext[this->capacity - 1] = -1;
			this->next = newNext;
		}

		// Die neue Zelle wird generiert
		Tuple elToAdd;
		elToAdd.row = i;
		elToAdd.column = j;
		elToAdd.value = e;

		// Man sucht die Position wo sie lexicographisch eingefugt wird
		prevNode = -1;
		int posToAdd = this->head;
		while (posToAdd != -1 && isLess(this->elements[posToAdd], elToAdd)) {
			prevNode = posToAdd;
			posToAdd = this->next[posToAdd];
		}
		if (this->head == -1) {
			posToAdd = 0;
		}


		int newElem = this->firstEmpty;
		this->firstEmpty = this->next[this->firstEmpty];
		this->elements[newElem] = elToAdd;
		this->next[newElem] = -1;

		if (posToAdd == 0) {
			// Einfugen auf dem ersten Stelle
			// Falls die Liste von Elementen nicht leer ist wird noch die Verbindung mit dem anderen Elemente der Liste ermoglicht
			if (this->head != -1) {
				this->next[newElem] = this->head;
			}
			this->head = newElem;
		}
		else {
			// Einfugen auf eine Stelle innerhalb der Liste oder auf dem letzten Stelle
			this->next[newElem] = posToAdd;
			this->next[prevNode] = newElem;
		}
		this->nrElements++;
		return NULL_TELEM;
	}
	throw exception();
}
