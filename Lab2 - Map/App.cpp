#include "ExtendedTest.h"
#include "ShortTest.h"
#include "ReplaceTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();
	testReplace();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


