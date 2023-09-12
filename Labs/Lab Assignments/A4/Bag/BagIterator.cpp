#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    this->currentBucket = 0;
    while(this->currentBucket < c.m && c.elements[this->currentBucket] == nullptr)
        this->currentBucket += 1;
    if(this->currentBucket < c.m)
        this->current = c.elements[this->currentBucket];
    else
        this->current = nullptr;
}
/// Best case: Theta(1)
/// Worst case: Theta(m)
/// Average case: O(m)

void BagIterator::first() {
    this->currentBucket = 0;
    while(this->currentBucket < this->bag.m && this->bag.elements[this->currentBucket] == nullptr)
        this->currentBucket += 1;
    if(this->currentBucket < this->bag.m)
        this->current = this->bag.elements[this->currentBucket];
    else
        this->current = nullptr;
}
/// Best case: Theta(1)
/// Worst case: Theta(m)
/// Average case: O(m)

void BagIterator::next() {
    if(!valid())
        throw exception();
    else{
        if(this->current->next != nullptr)
            this->current = this->current->next;
        else{
            this->currentBucket += 1;
            while(this->currentBucket < this->bag.m && this->bag.elements[this->currentBucket] == nullptr)
                this->currentBucket += 1;
            if(this->currentBucket <this->bag.m)
                this->current = this->bag.elements[this->currentBucket];
            else
                this->current = nullptr;
        }
    }
}
/// Best case: Theta(1)
/// Worst case: Theta(m)
/// Average case: O(m)

bool BagIterator::valid() const {
    if(this->bag.isEmpty())
        return false;
	if(this->currentBucket == this->bag.m)
        return false;
	else return true;
}
/// Theta(1)

TElem BagIterator::getCurrent() const
{
    if(!valid())
        throw exception();
    else
        return this->current->value;
}
/// Theta(1)