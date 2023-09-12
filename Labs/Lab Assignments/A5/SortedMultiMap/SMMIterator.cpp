#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->stack = new int[map.nrOfElements];
    this->first();
}
/// Theta(1)

void SMMIterator::first(){
    this->elems = -1;
    this->currentKey = this->map.root;
    while(this->currentKey != -1){
        this->elems += 1;
        this->stack[this->elems] = this->currentKey;
        this->currentKey = this->map.nodes[this->currentKey].left;
    }

    if(this->elems != -1){
        this->currentKey = this->stack[this->elems];
        this->currentValue = 0;
    }
    else{
        this->currentKey = -1;
        this->currentValue = -1;
    }
}
/// Best case: Theta(1)
/// Worst case: Theta(leftmost element) (?)
/// Average case:


void SMMIterator::next(){
    if(!valid())
        throw exception();

    if(this->map.nodes[this->currentKey].nr_of_values - 1 > this->currentValue){
        this->currentValue += 1;
    }
    else{
        this->currentKey = this->stack[this->elems];
        this->currentValue = 0;
        this->elems -= 1;

        if(this->map.nodes[currentKey].right != -1){
            this->currentKey = this->map.nodes[this->currentKey].right;
            while(this->currentKey != -1){
                this->elems += 1;
                this->stack[this->elems] = this->currentKey;
                this->currentKey = this->map.nodes[this->currentKey].left;
            }
        }
        if(this->elems != -1){
            this->currentKey = this->stack[this->elems];
        }
        else{
            this->currentKey = -1;
            this->currentValue = -1;
        }
    }
}
/// Best case: Theta(1)
/// Worst case: Theta(height of the current key) (?)
/// Average case:

bool SMMIterator::valid() const{
	if(this->currentKey == -1 || map.nrOfElements == 0)
        return false;
    return true;
}
/// Theta(1)

TElem SMMIterator::getCurrent() const{
	if(!valid())
        throw exception();
	TElem elem(this->map.nodes[this->currentKey].key, this->map.nodes[this->currentKey].values[this->currentValue]);
    return elem;
}
/// Theta(1)
