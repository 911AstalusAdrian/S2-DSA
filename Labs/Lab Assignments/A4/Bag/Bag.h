#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
typedef bool (*Condition)(TElem);
class BagIterator;

struct TNode{
    TElem value;
    TNode* next;
};

class Bag {
private:

    int m; /// size of the hashtable
    int nrOfElements; /// number of elements currently in the hashtable
    int hashFunction(TElem e) const; /// hash function
    float loadFactor;
    TNode **elements; /// array of pointers

    // why did I get errors when using TNode* elements[] ?
    void resize();
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
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

    //keeps in the bag only those elements that respect the given condition, cond
	void filter(Condition cond);
};