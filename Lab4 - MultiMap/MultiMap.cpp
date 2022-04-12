#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {

    this->m = 13;
    this->T = new Node*[m];
    this->elements = 0;
    int i=0;
    for(i=0; i<this->m; i++){
        this->T[i] = nullptr;
    }
}
// Theta(m)


void MultiMap::add(TKey c, TValue v) {

    int key = abs(c);
    int position = TFunction(key);
    Node* currentNode = this->T[position];

    while (currentNode != nullptr && currentNode->key != c){
        currentNode = currentNode->next;
    }

    if(currentNode == nullptr){

        Node* new_node = new Node;
        new_node->key = c;
        new_node->nodeCapacity = 2;
        new_node->nodeSize = 0;
        new_node->values = new TValue[new_node->nodeCapacity];
        new_node->values[new_node->nodeSize] = v;
        new_node->nodeSize++;
        new_node->next = this->T[position];

        this->T[position] = new_node;
    }
    else{

        if(currentNode->nodeSize == currentNode->nodeCapacity){
            currentNode->nodeCapacity = 2*currentNode->nodeCapacity;
            TValue* new_values = new TValue [currentNode->nodeCapacity];
            int i;
            for(i=0;i<currentNode->nodeSize;i++){
                new_values[i] = currentNode->values[i];
            }
            delete[] currentNode->values;
            currentNode->values = new_values;

        }
        currentNode->values[currentNode->nodeSize] = v;
        currentNode->nodeSize++;
    }

    this->elements++;
    float alpha = (float)(this->elements)/(float)(this->m);
    if(alpha>0.7){
        this->resize();
    }
}
//Best Case: Theta(1) - add an element on a new position of the hash table
//Worst Case: Theta(nrElements) - add an element at the last node of a position without causing a resize
//Total Complexity: O(m+ nrElements^2) - because of resizing the has table


bool MultiMap::remove(TKey c, TValue v) {

    int key = abs(c);
    int position = TFunction(key);
    Node* currentNode = this->T[position];

    while (currentNode != nullptr && currentNode->key != c){
        currentNode = currentNode->next;
    }
    if(currentNode == nullptr){
        return false;
    }
    else{
        int i = 0;
        bool found = false;
        while (!found && i<currentNode->nodeSize){
            if(currentNode->values[i] == v){
                found = true;
            }
            else{
                i++;
            }
        }
        if (found){
            currentNode->values[i] = currentNode->values[currentNode->nodeSize-1];
            currentNode->nodeSize--;
            if(currentNode->nodeSize==0){
                if(currentNode == this->T[position]){
                    this->T[position] = currentNode->next;
                }
                else{
                    Node* prevNode = this->T[position];
                    while(prevNode->next != currentNode){
                        prevNode = prevNode->next;
                    }
                    prevNode->next = currentNode->next;
                }
            }
            this->elements--;
            return true;
        }
        else{
            return false;
        }
    }
}
//Best Case: Theta(1) - the position where we search the element to delete has no element
//Worst Case: Theta(nrElements) - the element is the last one of a dynamic array
//Total Complexity: O(nrElements)


vector<TValue> MultiMap::search(TKey c) const {

    int key = abs(c);
    int position = TFunction(key);
    Node* currentNode = this->T[position];
    vector<TValue> values;

    while (currentNode != nullptr && currentNode->key != c){
        currentNode = currentNode->next;
    }

    if(currentNode != nullptr){
        int i = 0;
        for(i=0; i<currentNode->nodeSize; i++){
            values.push_back(currentNode->values[i]);
        }
    }
	return values;
}
//Best Case: Theta(1) - the position we try to search for elements does not have any
//Worst Case: Theta(nrElements) - the position has all the elements with different keys and the searched one is the last
//                              - the position has all the elements, but with only the searched key which contains all the elements
//Total Complexity: O(nrElements)

int MultiMap::size() const {

    return this->elements;
}
// Theta(1)

bool MultiMap::isEmpty() const {

    if(this->elements == 0){
        return true;
    }
	return false;
}
// Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
// Theta(1)

int MultiMap::TFunction(TKey k) const {

    return k%m;
}
// Theta(1)

int MultiMap::getKeyRange() const {
    if(this->elements == 0){
        return -1;
    }
    else{
        int maxKey = NULL_TVALUE;
        int minKey = NULL_TVALUE;
        for(int i = 0;i < this->m; i++){
            if(this->T[i] != nullptr){
                Node* currentNode = this->T[i];

                while (currentNode != nullptr){
                    if(maxKey == NULL_TVALUE || currentNode->key > maxKey){
                        maxKey = currentNode->key;
                    }
                    if(minKey == NULL_TVALUE || currentNode->key < minKey){
                        minKey = currentNode->key;
                    }
                    currentNode = currentNode->next;
                }
            }
        }
        return maxKey-minKey;
    }
}
// Theta(m) - we go through the whole hash table
// m > nrElements always

void MultiMap::resize() {

    TKey* keys = new TKey[this->elements];
    TValue* old_values = new TValue[this->elements];

    int i,j,k=0;
    for(i=0;i<this->m;i++){
        Node* current = this->T[i];
        Node* next;
        while(current != nullptr){
            for(j=0;j<current->nodeSize;j++){
                keys[k] = current->key;
                old_values[k] = current->values[j];
                k++;
            }
            next = current->next;
            current = next;
        }
    }

    for(i=0; i<this->m; i++){
        Node* current = this->T[i];
        Node* next;
        while(current != nullptr) {
            next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
    delete[] this->T;

    this->m = this->m*2;
    this->T = new Node*[m];
    this->elements = 0;
    for(i=0; i<this->m; i++){
        this->T[i] = nullptr;
    }

    for(i=0;i<k;i++){
        this->add(keys[i],old_values[i]);
    }
}
//Note: k = nrElements
//Best Case: Theta(m) - all the elements in the new hash table are on different positions
//Worst Case: Theta(m + nrElements^2) - all the elements in the new hash table are added on the same position
//Total Complexity: O(m+ nrElements^2)

MultiMap::~MultiMap() {

    int i;
    for(i=0; i<this->m; i++){
        Node* current = this->T[i];
        Node* next;
        while(current != nullptr) {
            next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
    delete[] this->T;
}
// Theta(nrElements)

