#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "IntersectionTest.h"
#include <stack>
#include <iostream>
using namespace std;




int main() {

	testAll();
	testAllExtended();

    IntersectionTest();


	cout << "That's all!" << endl;
	system("pause");

}



