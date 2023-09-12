#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <stdlib.h>

using namespace std;


Bag::Bag() {
	this->m = 10;
	this->nrOfElements = 0;
	this->loadFactor = (float)this->nrOfElements/(float)this->m;
	this->elements = new TNode*[this->m];
    for (int i=0;i<m;i++) {
        this->elements[i] = nullptr;
    }
}
/// Theta(m)


void Bag::resize() {
    this->m = this->m*2;
    TNode** new_table = new TNode*[this->m];
    for(int i=0;i<this->m;i++){
        new_table[i] = nullptr;
    }

    for(int i=0;i<this->m/2;i++){
        TNode* current = this->elements[i];
        while(current != nullptr){
            int index = hashFunction(current->value);
            TNode* new_current = new TNode;
            new_current->next = nullptr;
            new_current->value = current->value;
            if(new_table[index] == nullptr)
                new_table[index] = new_current;
            else{
                new_current->next = new_table[index];
                new_table[index] = new_current;
            }
            current = current->next;
        }
    }

    delete[] this->elements;
    this->elements = new_table;
}
/// Theta(m)


void Bag::add(TElem elem) {
    this->loadFactor = (float)(this->nrOfElements+1)/(float)this->m;
    if(loadFactor > 0.5)
        resize();

    int index = hashFunction(elem);
    /// on elements[index] we add our element
    TNode *new_node = new TNode();
    new_node->value = elem;
    new_node->next = nullptr;
    if(this->elements[index] == nullptr)
        this->elements[index] = new_node;
    else{
        new_node->next = this->elements[index];
        this->elements[index] = new_node;
    }
    this->nrOfElements += 1;
}
/// Theta(1)

bool Bag::remove(TElem elem) {
    if(!search(elem))
        return false;
    int index = hashFunction(elem);
    TNode* current = this->elements[index];
    TNode* prev = nullptr;

    while(current != nullptr && current->value != elem){
        prev = current;
        current = current->next;
    }

    if(prev == nullptr && current != nullptr)
        this->elements[index] = this->elements[index]->next;


    else if(current != nullptr){
        prev->next = current->next;
        current->next = nullptr;
    }
    delete current;
    this->nrOfElements -= 1;
    this->loadFactor = (float)this->nrOfElements/(float)this->m;
    return true;
}
/// Best case: Theta(1)
/// Worst case: Theta(n) - n is the number of elements in the sll at this->elements[index]
/// Average case: O(n)

bool Bag::search(TElem elem) const {
    int index = hashFunction(elem);
    TNode* current = this->elements[index];
    while (current != nullptr && current->value != elem)
        current = current->next;
    if(current != nullptr)
        return true;
    return false;
}
/// Best case: Theta(1)
/// Worst case: Theta(n) - n is the number of elements in the sll at this->elements[index]
/// Average case: O(n)

int Bag::nrOccurrences(TElem elem) const {
	int index = hashFunction(elem);
	int count = 0;
	TNode* current = this->elements[index];

	while (current != nullptr){
	    if (current->value == elem)
	        count += 1;
	    current = current->next;
	}
	return count;
}
/// Best case: Theta(1)
/// Worst case: Theta(n) - n is the number of elements in the sll at this->elements[index]
/// Average case: O(n)

int Bag::size() const {
	return this->nrOfElements;
}
/// Theta(1)

bool Bag::isEmpty() const {
	if (this->nrOfElements == 0)
	    return true;
	else return false;
}
/// Theta(1)


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
/// Theta(1)

Bag::~Bag() {
    for(int i=0;i<this->m;i++){
        TNode* node = this->elements[i];
        while(this->elements[i] != nullptr){
            node = this->elements[i]->next;
            delete this->elements[i];
            this->elements[i] = node;
        }
        this->elements[i] = node;
    }
}
/// Theta(m)

int Bag::hashFunction(TElem e) const {
    return abs(e) % m;
}

void Bag::filter(Condition cond) {
    for(int i=0;i<this->m;i++){
        TNode* prev = nullptr;
        TNode* current = this->elements[i];
        while(current != nullptr){
            if(!cond(current->value)) {
                if(current == this->elements[i]){
                    this->elements[i] = this->elements[i]->next;
                    current = this->elements[i];
                    prev = nullptr;
                    this->nrOfElements -= 1;
                }
                else{
                    prev->next = current->next;
                    this->nrOfElements -= 1;
                    current = prev;
                }
            }
            else{
                prev = current;
                current = current->next;
            }
        }
    }
}
/// Theta(m+nrOfElements)