#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {

	testAll();
	cout << "Short tests" << endl;
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}
