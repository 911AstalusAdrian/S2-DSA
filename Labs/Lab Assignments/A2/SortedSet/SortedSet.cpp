#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
    this->rel = r;
    this->head = NIL;
}
/// theta(1)

bool SortedSet::add(TComp e) {
    if(search(e))
        return false;
    // O(n)

    Node *new_node = new Node();
    new_node->value = e;
    new_node->next = NIL;
        /// empty list
    if (this->head == NIL) {
        this->head = new_node;
        return true;
    }
        /// elem is the new head
    else if (this->rel(new_node->value, this->head->value)) {
        new_node->next = this->head;
        this->head = new_node;
        return true;
    }

    Node* cn = this->head;
    while(cn->next != NIL && !this->rel(e, cn->next->value)){
        cn = cn->next;
    }
    new_node->next = cn->next;
    cn->next = new_node;
    return true;

}
/// best case - theta(1) - the element to add already exists on the first position
/// worst case - theta(n) - the element needs to be added at the end
/// average - O(n)

bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	Node* prev = NIL;
	Node* curr_node = this->head;
	while (curr_node != NIL && curr_node->value != elem){
	    prev = curr_node;
	    curr_node = curr_node->next;
	}

	/// remove the head
	if (prev == NIL && curr_node != NIL){
        this->head = this->head->next;
        return true;
	}

	/// regular removal
	else if (curr_node != NIL){
	    prev->next = curr_node->next;
	    curr_node->next = NIL;
        return true;
	}
	return false;
}
/// best case - theta(1) - we remove the head
/// worst case - theta(n) - we remove the last element
/// average case - O(n)


bool SortedSet::search(TComp elem) const {
	//TODO - Implementation
	Node* curr_node = this->head;
    while (curr_node != NIL) {
        if (curr_node->value == elem)
            return true;
        if(this->rel(elem, curr_node->value))
            return false;
        curr_node = curr_node->next;
    }
    return false;
}
/// best case - theta(1) - the element we search is the first one
/// worst case - theta(n) - the element we search is the last one
/// average case - O(n)

int SortedSet::size() const {
	//TODO - Implementation
	int size = 0;
	Node* current = this->head;
	while(current != NIL){
	    size++;
	    current = current->next;
	}
	return size;
}
/// theta(n)

bool SortedSet::isEmpty() const {
	//TODO - Implementation
	if (this->head == NIL)
        return true;
	else
	    return false;
}
/// theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
/// theta(1)

SortedSet::~SortedSet() {
	//TODO - Implementation
	Node* curr_node = this->head;
	Node* next;
    while (curr_node != NIL){
        next = curr_node->next;
        delete curr_node;
//        free(curr_node);
        curr_node = next;
    }
    this->head = NIL;

}
/// theta(n)
