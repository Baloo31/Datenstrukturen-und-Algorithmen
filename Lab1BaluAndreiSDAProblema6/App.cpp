#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {
	/*
	ADT Bag ñ repr‰sentiert als ein dynamisches Array von eindeutigen Elementen (E) und ein dynamisches Array von Positionen (P) in E der Elemente des Bags
	Zum Beispiel, das Bag [5, 10, -1, 2, 3, 10, 5, 5, -5] wird folgendermaﬂen repr‰sentiert:
	U = [5, 10, -1, 2, 3, -5]
	P = [0, 1, 2, 3, 4, 1, 0, 0, 5]
	*/
	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;
}