#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;

int main() {
	testAll();
	cout << "Short Tests Done\n";
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
}
