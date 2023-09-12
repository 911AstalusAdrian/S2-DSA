#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = this->bag.head;
	this->current_frequency = 1;
}
/// Theta(1)

void BagIterator::first() {
    this->current = this->bag.head;
    this->current_frequency = 1;
}
/// Theta(1)

void BagIterator::next() {
	if(current == -1)
        throw exception();
	if(this->current_frequency == this->bag.elements[current].info.second){
	    this->current = this->bag.elements[current].next;
	    this->current_frequency = 1;
	}
	else
	    this->current_frequency += 1;
}
/// Theta(1)

void BagIterator::previous() {
    if(current == -1 || this->bag.bagSize == 0)
        throw exception();
    if(this->current_frequency != 1)
        this->current_frequency -= 1;
    else{
        this->current = this->bag.elements[current].prev;
        if(this->current != 1)
            this->current_frequency = this->bag.elements[current].info.second;
    }
}
/// Theta(1)


bool BagIterator::valid() const {
	if(current == -1)
        return false;
    return true;
}
/// Theta(1)

TElem BagIterator::getCurrent() const
{
	if(current == -1)
        throw exception();
    return this->bag.elements[current].info.first;
}
/// Theta(1)
