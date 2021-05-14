#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
	testAll();
	std::cout << "Finished short tests\n";
	testAllExtended();

	std::cout << "Finished SMM Tests!" << std::endl;
	system("pause");
}
