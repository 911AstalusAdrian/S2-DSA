#include "Matrix.h"
#include <exception>
using namespace std;


positionPair Matrix::positionOf(TElem elem) const{
    positionPair positions;
    positions.first = -1;
    positions.second = -1;
    int i = 0;
    bool done = false;
    while (i<this->nrTriplets && !done){
        if(this->values[i] == elem){
            positions.first = this->lines[i];
            positions.second = this->cols[i];
            done = true;
        }
    }

    return positions;
}
/// Complexity
/// best case: theta(1) - the element we're looking for is the first one
/// worst case: theta(nrTriplets) - the element we're looking for is either last or not existent
/// average case: O(n)

Matrix::Matrix(int nrLines, int nrCols) {
    if(nrLines <=0 || nrCols <=0)
        throw exception();
    this->nr_lines = nrLines;
    this->nr_columns = nrCols;
    this->capacity = 10;
    this->lines = new TElem[this->capacity];
    this->cols = new TElem[this->capacity];
    this->values = new TElem[this->capacity];
    this->nrTriplets = 0;
}
/// theta(1)

Matrix::~Matrix() {
    delete[] this->lines;
    delete[] this->cols;
    delete[] this->values;
}
/// theta(1)

void Matrix::resize(){
    this->capacity = this->capacity * 2;
    TElem* new_lines = new TElem[capacity];
    TElem* new_cols = new TElem[capacity];
    TElem* new_values = new TElem[capacity];
    for (int i=0;i<nrTriplets; i++){
        new_lines[i] = lines[i];
        new_cols[i] = cols[i];
        new_values[i] = values[i];
    }

    this->lines = new_lines;
    this->cols = new_cols;
    this->values = new_values;
}
/// theta(nrTriplets)

int Matrix::nrLines() const {
    return this->nr_lines;
	return 0;
}
/// theta(1)

int Matrix::nrColumns() const {
    return this->nr_columns;
	return 0;
}
/// theta(1)

TElem Matrix::element(int i, int j) const {
    if(i < 0 || j < 0 || i >= nr_lines || j >= nr_columns)
        throw exception();
    for (int index=0; index<this->nrTriplets; index++){
        if (lines[index] == i && cols[index] == j)
            return values[index];
    }
    return NULL_TELEM;
}
/// best case: theta(1)
/// worst case: theta(nrTriplets)
/// average case: O(n)
// would while loop change the complexity?

TElem Matrix::modify(int i, int j, TElem e) {
    if(i < 0 || j < 0 || i >= nr_lines || j >= nr_columns)
        throw exception();
    TElem value = element(i, j);
    if (value == NULL_TELEM && e != NULL_TELEM){
        add_element(i, j, e);
        //value = element(i,j);
    }
    else if(value != NULL_TELEM && e != NULL_TELEM){
        change_element(i, j, e);
        //value = element(i,j);
    }
    else if(value != NULL_TELEM && e == NULL_TELEM){
        remove_element(i, j);
        //value = NULL_TELEM;
    }
	return value;
}
/// theta(1)

void Matrix::add_element(int i, int j, TElem e) {
    bool found = false;
    if(this->nrTriplets == 0){
        this->nrTriplets += 1;
        this->lines[0] = i;
        this->cols[0] = j;
        this->values[0] = e;
        found = true;
    }
    else {
        int index = 0;
        bool done = false;
        while (index < this->nrTriplets && !done) {
            if (this->lines[index] >= i && this->cols[index] > j) {
                shift_elements_right(index);
                this->lines[index] = i;
                this->cols[index] = j;
                this->values[index] = e;
                done = true;
                found = true;
            }
            index++;
        }
    }
    if (!found){
        if(this->nrTriplets == this->capacity)
            resize();
        this->lines[this->nrTriplets] = i;
        this->cols[this->nrTriplets] = j;
        this->values[this->nrTriplets] = e;
        this->nrTriplets += 1;
    }
}
/// theta(nrTriplets)


void Matrix::change_element(int i, int j, TElem e) {
    int index = 0;
    bool done = false;
    while (index < this->nrTriplets && !done){
        if (this->lines[index] == i && this->cols[index] == j){
            this->values[index] = e;
            done = true;
        }
        index++;
    }
}
/// best case: theta(1)
/// worst case: theta(nrTriplets)
/// average case: O(nrTriplets)

void Matrix::remove_element(int i, int j) {
    int index = 0;
    bool done = false;
    while(index < this->nrTriplets && !done){
        if(this->lines[index] == i && this->cols[index] == j){
            shift_elements_left(index);
            done = true;
        }
        index++;
    }
}
/// best case: theta(1)
/// worst case: theta(nrTriplets)
/// average case O(nrTriplets)

void Matrix::shift_elements_right(int index) {
    if(this->nrTriplets == this->capacity){
        resize();
    }
    this->nrTriplets += 1;
    for(int i=this->nrTriplets-1; i>index; i--){
        this->lines[i] = this->lines[i-1];
        this->cols[i] = this->cols[i-1];
        this->values[i] = this->values[i-1];
    }
}
/// O(nrTriplets-1)

void Matrix::shift_elements_left(int index) {
    for(int i=index; i<this->nrTriplets-1; i++){
        this->lines[i] = this->lines[i+1];
        this->cols[i] = this->cols[i+1];
        this->values[i] = this->values[i+1];
    }
    this->nrTriplets -= 1;
}
/// theta(nrTriplets-1)