//
// Created by Vlad on 07/04/2021.
//

#include "ReplaceTest.h"

#include <iostream>
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"

using namespace std;

void testReplace(){

    Map m;
    cout << "Test replace" << endl;
    assert(m.isEmpty() == true);
    assert(m.size() == 0); //add elements
    assert(m.add(5,5)==NULL_TVALUE);
    assert(m.add(1,111)==NULL_TVALUE);
    assert(m.add(10,110)==NULL_TVALUE);
    assert(m.add(7,7)==NULL_TVALUE);
    assert(m.add(1,1)==111);
    assert(m.add(10,10)==110);
    assert(m.add(-3,-3)==NULL_TVALUE);

    m.replace(10,10,13);
    assert(m.search(10) == 13);

    m.replace(1,10,13);
    assert((m.search(1) == 13) == false);
    assert((m.search(1) == 10) == false);
    assert(m.search(1) == 1);
}