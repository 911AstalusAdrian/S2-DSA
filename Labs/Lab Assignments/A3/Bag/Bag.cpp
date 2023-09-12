#include "Bag.h"
#include "BagIterator.h"
#include <exception>
using namespace std;


Bag::Bag() {
    this->capacity = 5000;
    this->bagSize = 0;
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->elements = new Node[this->capacity];
    for (int i=0; i < this->capacity; i++){
        if (i == 0){
            this->elements[i].next = i+1;
            this->elements[i].prev = -1;
        }
        else if (i == this->capacity-1){
            this->elements[i].next = -1;
            this->elements[i].prev = i-1;
        }
        else{
            this->elements[i].next = i+1;
            this->elements[i].prev = i-1;
        }
    }
}
/// Theta(n)


void Bag::add(TElem elem) {
    if(this->firstEmpty == -1)
        resize();

    /// add the first element
    if(this->bagSize == 0){
        TPair p;
        p.first = elem;
        p.second = 1;
        this->elements[this->firstEmpty].info = p;
        this->head = this->firstEmpty;
        this->tail = this->firstEmpty;
        this->firstEmpty = this->elements[this->firstEmpty].next;
        this->elements[this->tail].next = -1;
        this->bagSize += 1;
    }
    else{
        /// add a new element in the list
        if(!search(elem)){
            TPair p;
            p.first = elem;
            p.second = 1;
            this->elements[this->firstEmpty].info = p;
            this->elements[this->tail].next = this->firstEmpty;
            this->tail = this->firstEmpty;
            this->elements[this->firstEmpty].prev = this->tail;
            this->firstEmpty = this->elements[this->firstEmpty].next;
            this->elements[this->tail].next = -1;
            this->elements[this->firstEmpty].prev = -1;
            this->bagSize += 1;
        }
        else{
            /// we increase the frequency of an already existing element
            int current = this->head;
            bool done = false;
            while(current != -1 && !done){
                if(this->elements[current].info.first == elem) {
                    this->elements[current].info.second += 1;
                    done = true;
                    this->bagSize += 1;
                }
                current = this->elements[current].next;
            }
        }
    }
}
/// best case - theta(1) - empty bag
/// worst case - theta(n) - bag not empty
/// average case - O(n)

bool Bag::remove(TElem elem) {
    int current = this->head;
    while (current != -1){
        if(this->elements[current].info.first == elem){
            if(this->elements[current].info.second > 1){
                this->elements[current].info.second -= 1;
                this->bagSize -= 1;
                return true;
            }
            else{
                int prev = this->elements[current].prev;
                int next = this->elements[current].next;

                /// there's only one element to be removed
                if(prev == -1 && next == -1){
                    this->head = -1;
                    this->tail = -1;
                    this->elements[current].next = this->firstEmpty;
                    this->elements[current].prev = -1;
                    this->elements[this->firstEmpty].prev = current;
                    this->firstEmpty = current;
                    this->bagSize -= 1;
                    return true;
                }

                /// we remove the first element in the bag
                if(prev == -1){
                    this->head = next;
                    this->elements[this->head].prev = -1;
                    this->elements[current].next = this->firstEmpty;
                    this->elements[current].prev = this->tail;
                    this->elements[this->firstEmpty].prev = current;
                    this->firstEmpty = current;
                    this->bagSize -= 1;
                    return true;
                }

                /// we remove the last element in the bag
                if(next == -1){
                    this->tail = current;
                    this->elements[prev].next = -1;
                    this->bagSize -= 1;
                    return true;
                }
                else{
                    this->elements[prev].next = next;
                    this->elements[next].prev = prev;
                    this->elements[current].next = this->firstEmpty;
                    this->elements[current].prev = this->tail;
                    this->elements[this->firstEmpty].prev = current;
                    this->firstEmpty = current;
                    this->bagSize -= 1;
                    return true;
                }
            }
        }
        current = this->elements[current].next;
    }
    return false;
}
/// best case - theta(1) - elem is the first one
/// worst case - theta(n) - elem is the last one, or doesn't appear in the list
/// average case - O(n)

bool Bag::search(TElem elem) const {
    int current = head;
    int count = 0;
    while (current != -1 && count < this->bagSize){
        if (this->elements[current].info.first == elem)
            return true;
        current = this->elements[current].next;
        count++;
    }
    return false;
}
/// best case - theta(1) - elem is the first one
/// worst case - theta(n) - elem is the last one or not existent
/// average case - O(n)

int Bag::nrOccurrences(TElem elem) const {
    int current = head;
    while (current != -1) {
        if (this->elements[current].info.first == elem)
            return this->elements[current].info.second;
        current = this->elements[current].next;
    }
    return 0;
}
/// best case - theta(1) - elem is the first one in the list
/// worst case - theta(n) - elem is the last one in the list or not in the list at all
/// average case - O(n)

int Bag::size() const {
	return this->bagSize;
}
/// Theta(1)

bool Bag::isEmpty() const {
	if(this->bagSize == 0)
        return true;
	else
        return false;
}
/// Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
/// Theta(1)

Bag::~Bag() {
    delete[] this->elements;
}
/// Theta(1)

void Bag::resize() {
    Node* new_list = new Node[this->capacity*2];

    for (int i=0; i<this->capacity; i++)
        new_list[i]=this->elements[i];
    for (int i=this->capacity; i<this->capacity*2; i++)
    {
        if (i == this->capacity * 2 - 1) {
            new_list[i].next = -1;
            new_list[i].prev = i - 1;
        } else {
            new_list[i].next = i + 1;
            new_list[i].prev = i - 1;
        }
    }
    this->firstEmpty=this->capacity;
    this->capacity=this->capacity*2;
    delete [] this->elements;
    this->elements = new_list;
}