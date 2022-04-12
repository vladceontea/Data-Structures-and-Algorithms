#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{

    this->current_element = c.head;
    this->current_frequency = 1;

}
//Theta(1)


void BagIterator::first() {

    this->current_element = bag.head;
    this->current_frequency = 1;
}
//Theta(1)


void BagIterator::next() {

    if (this->current_element == -1){
        throw exception();
    }
    this->current_frequency += 1;
    if (this->current_frequency > this->bag.nodes[this->current_element].info.second){
        this->current_element = this->bag.nodes[this->current_element].next;
        this->current_frequency = 1;
    }
}
//Theta(1)


void BagIterator::jumpForward(int k){

    if (this->current_element == -1 || k <= 0){
        throw exception();
    }
    for (int i=0; i<k; i++){
        this->next();
        if (this->current_element == -1){
            i = k;
        }
    }

}
//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the Bag.
//throws an exception if the iterator is invalid or if k is negative or zero void
//Best Case: Theta(1) - the next element is the last one in the bag, so we stop
//Worst Case: Theta(k) - we are able to go through all the steps
//Total Complexity: O(k)


bool BagIterator::valid() const {

    if (this->current_element == -1){
        return false;
    }
    else{
        return true;
    }
}
//Theta(1)


TElem BagIterator::getCurrent() const
{
    if (this->current_element == -1){
        throw exception();
    }

    return this->bag.nodes[this->current_element].info.first;
}
//Theta(1)
