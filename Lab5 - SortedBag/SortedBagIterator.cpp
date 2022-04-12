#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

	this->currentNode = bag.root;
	this->currentFrequency = 1;
	this->stack = new BSTNode*[bag.nrElements];
	this->stackIndex = -1;

	while(this->currentNode != nullptr){
        this->stackIndex++;
	    this->stack[stackIndex] = this->currentNode;
	    this->currentNode = this->currentNode->left;
	}

	if (stackIndex != -1){
	    this->currentNode = this->stack[stackIndex];
	}
	else{
	    this->currentNode = nullptr;
	}
}
//Best Case: Theta(1) - the root has no left child
//Worst Case: Theta(n) - the tree is degenerate to the left
//Total Complexity: O(n)

TComp SortedBagIterator::getCurrent() {

    if(this->currentNode == nullptr){
        throw exception();
    }

    return this->currentNode->info;

}
//Theta(1)

bool SortedBagIterator::valid() {

    if(this->currentNode == nullptr){
        return false;
    }
    else{
        return true;
    }
}
//Theta(1)

void SortedBagIterator::next() {

    if(this->currentNode == nullptr){
        throw exception();
    }
    this->currentFrequency++;
    if (this->currentFrequency > this->currentNode->frequency){
        this->currentFrequency = 1;
        this->stackIndex--;
        if(this->currentNode->right != nullptr){
            this->currentNode = this->currentNode->right;
            while(this->currentNode != nullptr){
                this->stackIndex++;
                this->stack[this->stackIndex] = this->currentNode;
                this->currentNode = this->currentNode->left;
            }
        }
        if (stackIndex != -1){
            this->currentNode = this->stack[stackIndex];
        }
        else{
            this->currentNode = nullptr;
        }
    }
}
//Best Case: Theta(1) - the next element is another occurrence of the previous one
//Worst Case: Theta(n) - the right child of the current node is the root of a degenerate subtree to the left
//Total Complexity: O(n)

void SortedBagIterator::first() {
    this->stackIndex = -1;
    this->currentNode = this->bag.root;
    this->currentFrequency = 1;

    while(this->currentNode != nullptr){
        this->stackIndex++;
        this->stack[stackIndex] = this->currentNode;
        this->currentNode = this->currentNode->left;
    }

    if (stackIndex != -1){
        this->currentNode = this->stack[stackIndex];
    }
    else{
        this->currentNode = nullptr;
    }
}
//Best Case: Theta(1) - the root has no left child
//Worst Case: Theta(n) - the tree is degenerate to the left
//Total Complexity: O(n)
