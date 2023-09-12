#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    this->current = multime.head;
    this->current_index = 0;
	//TODO - Implementation
}
/// theta(1)


void SortedSetIterator::first() {
    this->current = multime.head;
    this->current_index = 0;
	//TODO - Implementation
}
/// theta(1)

void SortedSetIterator::next() {
	//TODO - Implementation
	if (this->current != NIL) {
        this->current = this->current->next;
        this->current_index += 1;
    }
	else{
	    throw exception();
	}
}
/// theta(1)

TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->current != NIL)
	    return this->current->value;
	else{
	    throw exception();
	}
	return NULL_TELEM;
}
/// theta(1)

bool SortedSetIterator::valid() const {
	//TODO - Implementation
	if (this->current != NIL)
        return true;
	else
	    return false;
}
/// theta(1)


void SortedSetIterator::jumpBackward(int k) {
    if (k <= 0 || !valid())
        throw exception();
    else if (this->current_index-k <0){
        this->current = NIL; /// make iterator invalid
    }
    /// we can jump k steps back
    else{
        int new_index = this->current_index - k;
        first();
        for(int i=0; i<new_index; i++)
            next();
    }
}
/// best case - theta(1) - we jump all the way to the first element
/// worst case - theta(n) - we jump from the last element to the second last
/// average case - O(n)

