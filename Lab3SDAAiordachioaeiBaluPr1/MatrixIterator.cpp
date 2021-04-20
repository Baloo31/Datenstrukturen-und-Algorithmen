#include <exception>
#include "MatrixIterator.h"
#include "Matrix.h"

using namespace std;


MatrixIterator::MatrixIterator(const Matrix& c) : mat(c)
{
	this->line = 0;
	this->column = 0;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void MatrixIterator::first() {
	this->line = 0;
	this->column = 0;
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
void MatrixIterator::next() {
	if (valid()) {
		if (this->column == this->mat.nrColumns() - 1) {
			this->column = 0;
			this->line++;
		}
		else {
			this->column++;
		}
	}
	else throw exception();
}


// best case: Theta(1); worst case: Theta(1); average case: Theta(1); general : Theta(1)
bool MatrixIterator::valid() const {
	if (this->line >= 0 && this->line < this->mat.nrLines() && this->column >= 0 && this->column < this->mat.nrColumns()) {
		return true;
	}
	return false;
}


// best case: Theta(1); worst case: Theta(n); average case: O(n); general : O(1)
TElem MatrixIterator::getCurrent() const
{
	if (valid()) {
		return this->mat.element(this->line, this->column);
	}
	else throw exception();
}
