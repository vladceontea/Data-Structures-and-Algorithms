//
// Created by Vlad on 24/03/2021.
//

#include "IntersectionTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <iostream>

using namespace std;


void IntersectionTest(){

    cout<<"Intersection Tests"<<endl;

    Set s, s2;
    assert(s.add(5)==true);
    assert(s.add(1)==true);
    assert(s.add(10)==true);
    assert(s.add(7)==true);
    assert(s.add(-3)==true);

    assert(s.size() == 5);

    assert(s2.add(5)==true);
    assert(s2.add(1)==true);
    assert(s2.add(11)==true);
    assert(s2.add(7)==true);
    assert(s2.add(3)==true);

    assert(s2.size() == 5);

    s.intersection(s2);

    assert(s.size() == 3);
    assert(s2.size() == 5);

    assert(s.search(-3)==false);
    assert(s.search(7)==true);

}