#include "Map.h"
#include "MapIterator.h"

Map::Map() {

    this->head = nullptr;
    this->tail = nullptr;
}
//Theta(1)

Map::~Map() {

    Node* current = this->head;
    Node* next;
    while(current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    this->tail = nullptr;
    this->head = nullptr;
}
//Theta(n)

TValue Map::add(TKey c, TValue v){

    Node* current;

    current = this->head;
    while(current != nullptr && current->info.first!=c){
        current = current->next;
    }

    if (current == nullptr){
        TElem new_elem;
        new_elem.first = c;
        new_elem.second = v;
        Node* new_node = new Node;
        new_node->info = new_elem;
        new_node->next = nullptr;
        new_node->prev = this->tail;

        if (this->head == nullptr){
            this->head = new_node;
            this->tail = new_node;
        }
        else{
            this->tail->next = new_node;
            this->tail = new_node;
        }
        return NULL_TVALUE;
    }
    else{

        int old_value = current->info.second;
        current->info.second = v;
        return old_value;
    }
}
//Best Case: Theta(1) - the key of the element we add is equal to the key of the head
//Worst Case: Theta(n) - the key of the element we add does not exist
//Total Complexity: O(n)

TValue Map::search(TKey c) const{

    Node* current;

    current = this->head;
    while(current != nullptr && current->info.first!=c){
        current = current->next;
    }
    if (current == nullptr){
        return NULL_TVALUE;
    }
    else{
        return current->info.second;
    }

}
//Best Case: Theta(1) - the key of the element we search for is equal to the key of the head
//Worst Case: Theta(n) - the key of the element we search for does not exist
//Total Complexity: O(n)

TValue Map::remove(TKey c){

    Node *current_node, *deleted_node;
    current_node = this->head;

    while(current_node != nullptr && current_node->info.first!=c){
        current_node = current_node->next;
    }
    deleted_node = current_node;
    if (current_node != nullptr){
        if (current_node == this->head){
            if (current_node == this->tail){
                this->head = nullptr;
                this->tail = nullptr;
            }
            else{
                this->head = this->head->next;
                this->head->prev = nullptr;
            }
        }
        else if (current_node == this->tail){
            this->tail = this->tail->prev;
            this->tail->next = nullptr;
        }
        else{
            current_node->next->prev = current_node->prev;
            current_node->prev->next = current_node->next;
        }
    }
    if(deleted_node == nullptr){
        return NULL_TVALUE;
    }
    else{
        return deleted_node->info.second;
    }

}
//Best Case: Theta(1) - the key of the element we remove is equal to the key of the head
//Worst Case: Theta(n) - the key of the element we remove does not exist
//Total Complexity: O(n)

void Map::replace(TKey k, TValue oldValue, TValue newValue){

    Node* current;

    current = this->head;
    while(current != nullptr && current->info.first!=k){
        current = current->next;
    }
    if (current!=nullptr){
        if(current->info.second == oldValue){
            current->info.second = newValue;
        }
    }
}
//Best Case: Theta(1) - the key of the element we want to replace is equal to the key of the head
//Worst Case: Theta(n) - the key of the element we want to replace does not exist
//Total Complexity: O(n)

int Map::size() const {

    int count = 0;
    Node* current = this->head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}
//Theta(n)

bool Map::isEmpty() const{

    if (this->head == nullptr){
        return true;
    }
    else{
        return false;
    }
}
//Theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



