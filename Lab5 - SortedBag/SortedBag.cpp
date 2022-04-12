#include <iostream>
#include <exception>
#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {

    this->root = nullptr;
    this->relation = r;
    this->nrElements = 0;

}
//Theta(1)

void SortedBag::add(TComp e) {

    BSTNode* current = this->root;
    bool found = false;

    while (current != nullptr && !found){
        if (current->info == e){
            current->frequency++;
            found = true;
        }
        else{
            if (this->relation(current->info, e)){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
    }

    if (!found){
        current = this->add_rec(this->root, e);
        if(this->root == nullptr){
            this->root = current;
        }
    }
    this->nrElements++;
}
//Best Case: Theta(1) - the element we add is another instance of the root
//Worst Case: Theta(n) - the element we add is not in the bst
//Total Complexity: O(n)

BSTNode* SortedBag::add_rec(BSTNode *node, TComp e) {

    if(node == nullptr){
        node = initNode(e);
    }
    else{
        if (!this->relation(node->info, e)){
            node->left = add_rec(node->left, e);
        }
        else{
            node ->right = add_rec(node->right, e);
        }
    }
    return node;
}
//Best Case: Theta(1) - the element we add is the second child of a degenerate tree
//Worst Case: Theta(n) - the element we add is on the last level of a degenerate tree
//Total Complexity: O(n)

BSTNode* SortedBag::initNode(TComp e) {

    BSTNode* node = new BSTNode;
    node->info = e;
    node->left = nullptr;
    node->right = nullptr;
    node->frequency = 1;
    return node;
}
//Theta(1)


bool SortedBag::remove(TComp e) {

    BSTNode* current = this->root;
    bool found = false;

    while (current != nullptr && !found){
        if (current->info == e){
            found = true;
        }
        else{
            if (this->relation(current->info, e)){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
    }

    if (!found){
        return false;
    }
    else{
        if (current->frequency > 1){
            current->frequency--;
        }
        else {
                if (current->left == nullptr && current->right == nullptr) {
                    BSTNode* parent = this->findParent(current);
                    if (parent != nullptr) {
                        if (parent->right == current) {
                            parent->right = nullptr;
                        } else {
                            parent->left = nullptr;
                        }
                    }
                    else{
                        this->root = nullptr;
                    }
                }
                if (current->left != nullptr && current->right == nullptr){
                    BSTNode* parent = this->findParent(current);
                    if (parent != nullptr){
                        if(parent->right == current){
                            parent->right = current->left;
                        }
                        else{
                            parent->left = current->left;
                        }
                    }
                    else{
                        this->root = current->left;
                    }
                }
                if (current->left == nullptr && current->right != nullptr){
                    BSTNode* parent = this->findParent(current);
                    if (parent != nullptr) {
                        if (parent->right == current) {
                            parent->right = current->right;
                        } else {
                            parent->left = current->right;
                        }
                    }
                    else{
                        this->root = current->right;
                    }
                }
                if (current->left != nullptr && current->right != nullptr){

                    BSTNode* minimum = findMinimumMaximum(current->right);

                    int value = minimum->info;
                    int valueFreq = minimum->frequency;

                    this->remove(minimum->info);
                    current->info = value;
                    current->frequency = valueFreq;
            }
        }
        this->nrElements--;
        return true;
    }

}
//Best Case: Theta(1) - the element we remove is the root, when it has a frequency larger than one
//Worst Case: Theta(n) - the element we remove is the leaf of a degenerate tree
//Total Complexity: O(n)

BSTNode* SortedBag::findParent(BSTNode *node) {

    BSTNode *parent = this->root;
    if (parent == node) {
        parent = nullptr;
    } else {
        while (parent != nullptr && parent->left != node && parent->right != node) {
            if (!relation(parent->info, node->info)) {
                parent = parent->left;
            } else {
                parent = parent->right;
            }
        }
    }
    return parent;
}
//Best Case: Theta(1) - the node we are searching the parent of is the root
//Worst Case: Theta(n) - the node we are searching the parent of is a leaf
//Total Complexity: O(n)

BSTNode* SortedBag::findMinimumMaximum(BSTNode *node) {

    BSTNode* minimum = node;

    while(minimum->left != nullptr){
        minimum = minimum->left;
    }

    return minimum;
}
//Theta(h)
//Will return the minimum of the right side in case of <= (could be replaced with finding the maximum of left side)
//Will return the maximum of the right side in case of >= (could be replaced with finding the minimum of right side)
//Since the operation is reversed, the required component is also reversed for the two cases

int SortedBag::removeOccurrences(int nr, TComp elem) {

    if (nr<0){
        throw std::exception();
    }
    int number = std::min(nr, nrOccurrences(elem));
    for (int i=0; i<number; i++){
        this->remove(elem);
    }
    return number;
}
//Best Case: Theta(nrOccurrences + nr) - the element we remove is the root and we remove all its occurrences
//Worst Case: Theta(n*nrOccurrences) - the element we remove is the leaf of a degenerate tree and we remove all the occurrences
//Total Complexity: O(n*nrOccurrences)

bool SortedBag::search(TComp elem) const {
    BSTNode* current = this->root;

    while (current != nullptr){
        if (current->info == elem){
            return true;
        }
        else{
            if (this->relation(current->info, elem)){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
    }
    return false;
}
//Best Case: Theta(1) - the node we search for is the root
//Worst Case: Theta(n) - the node we search for is not in the tree (degenerate)
//Total Complexity: O(n)

int SortedBag::nrOccurrences(TComp elem) const {
    BSTNode* current = this->root;

    while (current != nullptr){
        if (current->info == elem){
            return current->frequency;
        }
        else{
            if (this->relation(current->info, elem)){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
    }
    return 0;
}
//Best Case: Theta(1) - the node we search for is the root
//Worst Case: Theta(n) - the node we search for is not in the tree (degenerate)
//Total Complexity: O(n)


int SortedBag::size() const {

    return this->nrElements;

}
//Theta(1)

bool SortedBag::isEmpty() const {

    if(this->nrElements == 0){
        return true;
    }
	return false;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)

SortedBag::~SortedBag() {

    this->destroy(this->root);

}
//Theta(n)

void SortedBag::destroy(BSTNode *node) {

    if(node != nullptr){
        this->destroy(node->left);
        this->destroy(node->right);
        delete node;
    }
}
//Theta(n)