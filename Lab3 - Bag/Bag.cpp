#include "Bag.h"
#include "BagIterator.h"
#include <exception>

using namespace std;


Bag::Bag() {

    this->capacity = 5;
    this->nodes = new Node[this->capacity];

    int i;
    for (i=0;i<this->capacity-1;i++){
        this->nodes[i].next = i+1;
    }
    this->nodes[this->capacity-1].next = -1;
    this->nodes[0].prev = -1;
    for (i=1;i<this->capacity;i++){
        this->nodes[i].prev = i-1;
    }
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->nrElements = 0;
}
//Theta(n) - where n = capacity


Bag::~Bag() {

    delete[] this->nodes;
    this->nodes = nullptr;
}
//Theta(1)


int Bag::allocate() {

    int newElem;
    newElem = this->firstEmpty;
    if (newElem!=-1){
        this->firstEmpty = this->nodes[this->firstEmpty].next;
        if (this->firstEmpty != -1) {
            this->nodes[this->firstEmpty].prev = -1;
        }
        this->nodes[newElem].next = -1;
        this->nodes[newElem].prev = -1;
    }
    return newElem;
}
//Theta(1)


int Bag::free(int position) {

    this->nodes[position].next = this->firstEmpty;
    this->nodes[position].prev = -1;
    if (this->firstEmpty != -1) {
        this->nodes[this->firstEmpty].prev = position;
    }

    return position;
}
//Theta(1)


void Bag::resize(){

    Node* new_nodes = new Node[this->capacity*2];

    int i;
    for (i=0;i<this->capacity;i++){
        new_nodes[i].prev = this->nodes[i].prev;
        new_nodes[i].next = this->nodes[i].next;
        new_nodes[i].info = this->nodes[i].info;
    }

    for(i=this->capacity;i<this->capacity*2-1;i++){
        new_nodes[i].next = i+1;
    }

    new_nodes[this->capacity*2-1].next = -1;
    for (i=this->capacity;i<=this->capacity*2;i++){
        new_nodes[i].prev = i-1;
    }

    delete[] this->nodes;

    this->firstEmpty = this->capacity;

    this->capacity *= 2;
    this->nodes = new_nodes;

}
//Theta(n)
//We have 3 for loops of size n and Theta(3n) = Theta(n)


void Bag::add(TElem elem) {

    int current;
    current = this->head;
    while (current != -1 && this->nodes[current].info.first != elem){
        current = this->nodes[current].next;
    }

    if (current != -1){
        this->nodes[current].info.second += 1;
    }
    else{
        int newElem;
        newElem = allocate();
        if (newElem == -1){
            this->resize();
            newElem = allocate();
        }
        TBagElem newBagElem;
        newBagElem.first = elem;
        newBagElem.second = 1;
        this->nodes[newElem].info = newBagElem;
        if (this->head == -1){
            this->head = newElem;
            this->tail = newElem;
        }
        else{
            this->nodes[newElem].next = this->head;
            this->nodes[this->head].prev = newElem;
            this->head = newElem;
        }
    }
    this->nrElements++;
}
//Best Case: Theta(1) - the element we try to add already exists and is the head
//Worst Case: Theta(n) - the element we try to add is not already in the bag
//Total Complexity: O(n)


bool Bag::remove(TElem elem) {

    int current;
    current = this->head;
    while (current != -1 && this->nodes[current].info.first != elem){
        current = this->nodes[current].next;
    }

    if (current == -1){
        return false;
    }
    else{
        if (this->nodes[current].info.second > 1){
            this->nodes[current].info.second--;
        }
        else{
            if (current == this->head){
                if(current == this->tail){
                    this->head = -1;
                    this->tail = -1;
                }
                else{
                    this->head = this->nodes[this->head].next;
                    this->nodes[this->head].prev = -1;
                }
            }
            else if (current == this->tail){
                this->tail = this->nodes[this->tail].prev;
                this->nodes[this->tail].next = -1;
            }
            else{
                this->nodes[this->nodes[current].next].prev = this->nodes[current].prev;
                this->nodes[this->nodes[current].prev].next = this->nodes[current].next;
            }
            this->nodes[current].info.second--;
            this->firstEmpty = free(current);
        }

        this->nrElements--;
        return true;
    }
}
//Best Case: Theta(1) - the element we try to remove is the head
//Worst Case: Theta(n) - the element we try to remove is not in the bag
//Total Complexity: O(n)


bool Bag::search(TElem elem) const {

    int current;
    current = this->head;
    while (current != -1 && this->nodes[current].info.first != elem){
        current = this->nodes[current].next;
    }

    if (current != -1){
        return true;
    }
    else{
        return false;
    }
}
//Best Case: Theta(1) - the element we search for is the head
//Worst Case: Theta(n) - the element we search for is not in the bag
//Total Complexity: O(n)


int Bag::nrOccurrences(TElem elem) const {

    int current;
    current = this->head;
    while (current != -1 && this->nodes[current].info.first != elem){
        current = this->nodes[current].next;
    }

    if (current != -1){
        return this->nodes[current].info.second;
    }
    else{
        return 0;
    }
}
//Best Case: Theta(1) - the element we want to return the frequency of is the head of the bag
//Worst Case: Theta(n) - the element we want to return the frequency of is not in the bag
//Total Complexity: O(n)


int Bag::size() const {

    return this->nrElements;
}
//Theta(1)


bool Bag::isEmpty() const {

    if (this->nrElements == 0){
        return true;
    }
    else{
        return false;
    }
}
//Theta(1)


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//Theta(1)