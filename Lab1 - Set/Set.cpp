#include "Set.h"
#include "SetIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Set::Set() {
	this->length = 0;
	this->capacity = 10;
	this->elements = new TElem[this->capacity];
}
//Theta(1)

Set::~Set() {

    delete[] this->elements;
}
//Theta(1)

void Set::resize() {

    this->capacity *= 2;
    TElem* new_set = new TElem[this->capacity];

    int i;
    for(i=0; i<this->length; i++){
        new_set[i] = this->elements[i];
    }

    delete[] this->elements;

    this->elements = new_set;
}
//Theta(length)

void Set::intersection(const Set &s){

    int index = 0;

    while (index < this->length) {
        int index_s = 0;
        bool found = false;
        while (!found && index_s < s.length) {
            if (this->elements[index] == s.elements[index_s]) {
                found = true;
            }
            index_s++;
        }
        if (!found){
            this->elements[index] = this->elements[this->length - 1];
            this->length--;
        }
        else{
            index++;
        }
    }
}
// Best Case: Theta(length^2 + length*s_length), Worst Case: Theta(length*s.length) => Total Complexity: O(length*s.length)
// if length < s.length and the intersection is the original set, the BC will be length^2 (smaller than length*s.length)
// for the WC, it means that none of the elements in the original set is in s
// if length > s.length, TC of length^2 is impossible

bool Set::add(TElem elem) {
    if (this->capacity == this->length){
        resize();
    }

    int index = 0;
    bool found = false;
    while (!found && index<this->length){
        if(this->elements[index] == elem){
            found = true;
        }
        index++;
    }
    if (found){
        return false;
    }
    else{
        this->elements[this->length] = elem;
        this->length++;
        return true;
    }
}
// Best Case: Theta(1), Worst Case: Theta(length) => Total Complexity: O(length)


bool Set::remove(TElem elem) {
    int index = 0;
    bool found = false;
    while (index<this->length && !found){
        if(this->elements[index] == elem){
            found = true;
        }
        else{
            index++;
        }
    }

    if(!found){
        return false;
    }
    else{
        this->elements[index] = this->elements[this->length - 1];
        this->length--;
        return true;
    }
}
// Best Case: Theta(1), Worst Case: Theta(length) => Total Complexity: O(length)

bool Set::search(TElem elem) const {
    int index = 0;
    bool found = false;
    while (index<this->length && !found){
        if(this->elements[index] == elem){
            found = true;
        }
        else{
            index++;
        }
    }

    if(!found){
        return false;
    }
    else{
        return true;
    }
}
// Best Case: Theta(1), Worst Case: Theta(length) => Total Complexity: O(length)

int Set::size() const {
	return this->length;
}
//Theta(1)

bool Set::isEmpty() const {
	if(this->length == 0){
	    return true;
	}
	else{
	    return false;
	}
}
//Theta(1)

SetIterator Set::iterator() const {
	return SetIterator(*this);
}


