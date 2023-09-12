#pragma once
#include <utility>
//DO NOT CHANGE THIS PART
typedef int TElem;
typedef std::pair<int,int> positionPair;
#define NULL_TELEM 0


class Matrix {

private:
    TElem* lines;
    TElem* cols;
    TElem* values;
    int nr_lines;
    int nr_columns;
    int nrTriplets;
    int capacity;

	//TODO - Representation

	//resize function for the dynamic arrays
	void resize();

	//add an element (value on the line & col) in our triplet of dynamic arrays
	void add_element(int i, int j, TElem e);

	// change an element (value on the line & col) in our triplet of dynamic arrays
	void change_element(int i, int j, TElem e);

	// remove an element from our triplet of dynamic arrays
	void remove_element(int i, int j);

	// shifts all the elements starting from index to the right
	void shift_elements_right(int index);

	// shifts all the elements starting from the index to the left
	void shift_elements_left(int index);

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//destructor
	~Matrix();

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    //returns the position of element elem from the Matrix (as a line, column pair).
    // If elem occurs multiple times, any position where it appears is fine.
    // If elem is not in the Matrix, return the pair <-1, -1>.
    positionPair positionOf(TElem elem) const;

};
