#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {
	testAll();
	cout << "Short tests over" << endl;

    testFilter();
    cout << "Filter works. Wow!" << endl;

    testAllExtended();
	cout << "All test over" << endl;

    return 0;

}