#include "ShortTest.h"
#include <assert.h>
#include <iostream>
#include "Bag.h"
#include "BagIterator.h"

bool pos(TElem e){
    if(e > 0)
        return true;
    else return false;
}

bool gt5(TElem e){
    if(e > 5)
        return true;
    else
        return false;
}

bool hundred(TElem e){
    if (e > 100)
        return true;
    else
        return false;
}

bool two_digit(TElem e){
    if(e >= -99 && e <= 99)
        return true;
    else
        return false;
}


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }
}

void testFilter(){
    Bag b1;
    b1.add(5);
    b1.add(1);
    b1.add(10);
    b1.add(7);
    b1.add(1);
    b1.add(11);
    b1.add(-3);
    b1.filter(pos);

    assert(b1.size() == 6);


    Bag b2;
    b2.add(5);
    b2.add(1);
    b2.add(10);
    b2.add(7);
    b2.add(1);
    b2.add(11);
    b2.add(-3);
    b2.filter(gt5);
    assert(b2.size() == 3);

    Bag b3;
    b3.add(5);
    b3.add(1);
    b3.add(10);
    b3.add(7);
    b3.add(1);
    b3.add(11);
    b3.add(-3);
    b3.filter(hundred);
    assert(b3.size() == 0);

    Bag b4;
    b4.add(5);
    b4.add(1);
    b4.add(10);
    b4.add(7);
    b4.add(1);
    b4.add(11);
    b4.add(-3);
    b4.filter(two_digit);
    assert(b4.size() == 7);


}
