
#include "ValueIterator.h"
ValueIterator::ValueIterator(const SortedMultiMap &d, TKey k): map(d), key(k){
    vector<TValue> search_results = this->map.search(this->key);
    this->cap = search_results.size();
    this->values = new TValue [this->cap];
    for(int i=0;i<this->cap;i++)
        this->values[i] = search_results[i];
    this->current = 0;
}
///

void ValueIterator::first() {
    this->current = 0;
}
/// Theta(1)

void ValueIterator::next() {
    this->current += 1;
}
/// Theta(1)

bool ValueIterator::valid() const {
    if(this->cap == 0 || this->current == this->cap)
        return false;
    return true;
}
/// Theta(1)

TValue ValueIterator::getCurrent() const {
    return this->values[this->current];
}
/// Theta(1)

