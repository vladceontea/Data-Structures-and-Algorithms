#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {


	testAll();
	testKeyRange();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
