#pragma once
#include <utility>
#define NULL_TELEM -111111;
typedef std::pair<int, int> TPair;
typedef int TElem;
class BagIterator;


class Bag {


private:
    struct Node{
        TPair info;
        int next;
        int prev;
    };
    Node* elements;
    int capacity;
    int head;
    int tail;
    int firstEmpty;
    int bagSize;


	friend class BagIterator;
	void resize();
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();

};