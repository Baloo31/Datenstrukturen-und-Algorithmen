#pragma once

#include "Matrix.h"

class MatrixIterator
{
	//DO NOT CHANGE THIS PART
	friend class Matrix;

private:
	const Matrix& mat;
	int line;
	int column;
	MatrixIterator(const Matrix& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
