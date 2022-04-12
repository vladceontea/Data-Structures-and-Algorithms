#include <iostream>
#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {

    this->currentPos = 0;
    while(this->currentPos < this->col.m && this->col.T[this->currentPos] == nullptr){
        this->currentPos = this->currentPos+1;
    }
    if(this->currentPos < this->col.m){
        this->currentNode = this->col.T[this->currentPos];
    }
    else{
        this->currentNode = nullptr;
    }
    this->nodePos = 0;
}
//Best Case: Theta(1) - the first position has an element
//Worst Case: Theta(m) - only the last position has elements
//Total Complexity: O(m)

TElem MultiMapIterator::getCurrent() const{

    if(this->currentNode == nullptr){
        throw exception();
    }

    TElem element;
    TKey c;
    TValue v;
    c = this->currentNode->key;
    v = this->currentNode->values[this->nodePos];

    element.first = c;
    element.second = v;

	return element;
}
// Theta(1)

bool MultiMapIterator::valid() const {

    if(this->currentNode == nullptr){
        return false;
    }
    else{
        return true;
    }

}
// Theta(1)

void MultiMapIterator::next() {

    if(this->currentNode == nullptr){
        throw exception();
    }


    if(this->nodePos == this->currentNode->nodeSize-1){
        this->currentNode = this->currentNode->next;
        this->nodePos = 0;
    }
    else{
        if(this->nodePos < this->currentNode->nodeSize-1) {
            this->nodePos++;
        }
    }


    if(this->currentNode == nullptr){
        this->currentPos++;
        while(this->currentPos < this->col.m && this->col.T[this->currentPos] == nullptr){
            this->currentPos = this->currentPos+1;
        }
        if(this->currentPos < this->col.m){
            this->currentNode = this->col.T[this->currentPos];
        }
    }
}
// Best Case: Theta(1) - we go tot the next position in the dynamic array of the node or the next node in the linked list
// Worst Case: Theta(m) - going from the first position in the hash table to the end without finding another element
// Total Complexity: O(m)

void MultiMapIterator::first() {

    this->currentPos = 0;
    while(this->currentPos < this->col.m && this->col.T[this->currentPos] == nullptr){
        this->currentPos = this->currentPos+1;
    }
    if(this->currentPos < this->col.m){
        this->currentNode = this->col.T[this->currentPos];
    }
    else{
        this->currentNode = nullptr;
    }
    this->nodePos = 0;
}
//Best Case: Theta(1) - the first position has an element
//Worst Case: Theta(m) - only the last position has elements
//Total Complexity: O(m)
