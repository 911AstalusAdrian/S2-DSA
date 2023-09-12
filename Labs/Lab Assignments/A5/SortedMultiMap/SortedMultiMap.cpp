#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r){
    this->rel = r;
    this->firstEmpty = 0;
    this->root = -1;
    this->nrOfElements = 0;
    this->nrOfKeys = 0;
    this->capacity = 10;
    this->nodes = new Node[this->capacity];
    for(int i=0;i<this->capacity;i++){
        nodes[i].key = -1;
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
        nodes[i].nr_of_values = 0;
        nodes[i].values_cap = 0;
    }
}
/// Theta(capacity)

void SortedMultiMap::add(TKey c, TValue v) {
	int current = this->root;

	/// Empty tree
	if(current == -1){
	    this->root = 0;
	    this->firstEmpty += 1;
	    this->nodes[0].key = c;
	    this->nodes[0].values = new int[2];
	    this->nodes[0].values_cap = 2;
	    this->nodes[0].nr_of_values = 1;
	    this->nodes[0].values[0] = v;
	    this->nrOfKeys += 1;
	}

	/// Searching for the node having the key c
	else{
        int previous = this->root;
        while(current != -1){
            previous = current;

            /// Found the key c
            if(this->nodes[current].key == c){
                /// array of corresponding values needs resizing
                if(nodes[current].values_cap == nodes[current].nr_of_values)
                    resizeKeyValues(current);
                /// adding the new value at the end of the array
                this->nodes[current].values[nodes[current].nr_of_values] = v;
                this->nodes[current].nr_of_values += 1;
                this->nrOfElements += 1;
                return;
            }

            /// choosing the branch on which to continue
            else if(this->rel(c, this->nodes[current].key))
                current = nodes[current].left;
            else
                current = nodes[current].right;
        }
        /// the entire tree needs resizing
        if(this->nrOfKeys == this->capacity)
            resizeTree();


        this->nrOfKeys += 1;
        nodes[this->firstEmpty].parent = previous;
        this->nodes[firstEmpty].key = c;
        if(nodes[firstEmpty].values_cap == 0){
            this->nodes[firstEmpty].values = new int[2];
            this->nodes[firstEmpty].values_cap = 2;
            this->nodes[firstEmpty].nr_of_values = 0;
        }
        this->nodes[firstEmpty].values[this->nodes[firstEmpty].nr_of_values] = v;
        this->nodes[firstEmpty].nr_of_values += 1;


        if(this->rel(c, this->nodes[previous].key))
            nodes[previous].left = firstEmpty;
        else nodes[previous].right = firstEmpty;
        this->firstEmpty += 1;
	}
	this->nrOfElements += 1;
}
/// Best case: Theta(1)
/// Worst case: Theta(height of the tree) (?)
/// Average case:

vector<TValue> SortedMultiMap::search(TKey c) const {
	int current = this->root;
	while(current != -1){
	    if(this->nodes[current].key == c){
	        std::vector<int> values;
	        for(int i=0;i< this->nodes[current].nr_of_values; i++)
	            values.push_back(nodes[current].values[i]);
            return values;
	    }

	    else if(this->rel(c, this->nodes[current].key))
	        current = nodes[current].left;
	    else
	        current = nodes[current].right;
	}
    return vector<TValue>();
}
/// Best case: Theta(1)
/// Worst case: Theta(height of tree + nr of values of the key)

bool SortedMultiMap::remove(TKey c, TValue v) {
    int current = this->root;
    int prev=this->root;
    while (current != -1) {
        if (this->nodes[current].key == c) {
            if (this->nodes[current].nr_of_values > 1) {
                for (int i = 0; i < this->nodes[current].nr_of_values; i++)
                {

                    if (this->nodes[current].values[i] == v) {
                        for(int j = i; j < nodes[current].nr_of_values - 1; ++j)
                            nodes[current].values[j] = nodes[current].values[j + 1];
                        nodes[current].nr_of_values--;
                        this->nrOfElements--;
                        return true;
                    }
                }
                return false;
            }
            else if(this->nodes[current].values[0] == v){
                if (nodes[current].right != -1 && nodes[current].left != -1) {
                    int aux = nodes[current].right;
                    while (nodes[aux].left != -1) {
                        aux = nodes[aux].left;
                    }

                    if (!this->rel(this->nodes[current].key, this->nodes[prev].key))
                        nodes[prev].right = aux;
                    else
                        nodes[prev].left = aux;

                    if (this->root == current) {
                        this->root = aux;
                    }


                    nodes[nodes[current].right].parent = nodes[current].parent;
                    nodes[nodes[current].left].parent = nodes[current].parent;
                }
                else if(nodes[current].right != -1) {
                    if (this->root == current) {
                        this->root = nodes[current].right;
                    }

                    if (this->rel(this->nodes[current].key, this->nodes[prev].key))
                        nodes[prev].right = nodes[current].right;
                    else
                        nodes[prev].left =  nodes[current].right;

                    nodes[nodes[current].right].parent = nodes[current].parent;
                }
                else if (nodes[current].left != -1) {
                    if (this->root == current) {
                        this->root = nodes[current].left;
                    }

                    if (this->rel(this->nodes[current].key, this->nodes[prev].key))
                        nodes[prev].right = nodes[current].left;
                    else
                        nodes[prev].right = nodes[current].left;

                    nodes[nodes[current].left].parent = nodes[current].parent;
                }
                else {
                    if (this->rel(c, this->nodes[prev].key))
                        nodes[prev].left = -1;
                    else
                        nodes[prev].right = -1;
                }

                nodes[current].parent = -1;
                nodes[current].left = -1;
                nodes[current].right = -1;
                nodes[current].nr_of_values = 0;
                nodes[current].values_cap = 0;
                this->firstEmpty = current;

                this->nrOfElements--;
                return true;
            }
            return false;
        }
        else if (this->rel(c, this->nodes[current].key)) {
            prev = current;
            current = nodes[current].left;
        }
        else {
            prev = current;
            current = nodes[current].right;
        }
    }
    return false;
}
/// Best case: Theta(1)
/// Worst case:
/// Average case:

int SortedMultiMap::size() const {
    return this->nrOfElements;
}
/// Theta(1)

bool SortedMultiMap::isEmpty() const {
	if(this->nrOfElements == 0)
        return true;
	else return false;
}
/// Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
/// Theta(1)

SortedMultiMap::~SortedMultiMap() {
	delete[] this->nodes;
}
/// Theta(1)

void SortedMultiMap::resizeTree() {
    Node* newTree = new Node[this->capacity * 2];
    this->firstEmpty = this->capacity;
    for(int i=0;i<this->capacity;i++){
        newTree[i] = this->nodes[i];
    }
    for(int i=this->capacity;i<this->capacity*2;i++){
        newTree[i].key = -1;
        newTree[i].left = -1;
        newTree[i].right = -1;
        newTree[i].parent = -1;
        newTree[i].nr_of_values = 0;
        newTree[i].values_cap = 0;
    }

    delete[] this->nodes;
    this->nodes = newTree;
    this->capacity *= 2;
}
/// Theta(capacity)


void SortedMultiMap::resizeKeyValues(int current) {
    int *newValues = new int[this->nodes[current].values_cap * 2];
    for(int i=0; i < this->nodes[current].values_cap; i++){
        newValues[i] = this->nodes[current].values[i];
    }

    for(int i=this->nodes[current].values_cap; i<this->nodes[current].values_cap * 2; i++)
        newValues[i] = -1;

    delete this->nodes[current].values;
    this->nodes[current].values = newValues;
    this->nodes[current].values_cap *= 2;
}
/// Theta(values_cap) - the capacity of the dynamic array corresponding to the key
