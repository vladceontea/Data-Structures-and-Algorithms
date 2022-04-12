#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    this->current_element = d.head;
}
//Theta(1)

void MapIterator::first() {

    this->current_element = map.head;
}
//Theta(1)

void MapIterator::next() {

    if (this->current_element == nullptr){
        throw exception();
    }
    this->current_element = this->current_element->next;
}
//Theta(1)

TElem MapIterator::getCurrent(){

    if (this->current_element == nullptr){
        throw exception();
    }
    return this->current_element->info;

}
//Theta(1)

bool MapIterator::valid() const {

    if (this->current_element != nullptr){
        return true;
    }
    else{
        return false;
    }
}
//Theta(1)


