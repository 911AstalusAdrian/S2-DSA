#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include "iostream"


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

	Bag b2;
    b2.add(5);
    b2.add(1);
    b2.add(10);
    b2.add(7);
    b2.add(1);
    b2.add(11);
    b2.add(-3);
	BagIterator it2 = b2.iterator();
	it2.first();  // 5
    it2.next(); // 1
    it2.previous();
    assert(it2.getCurrent() == 5);
    it2.next(); // 1
    it2.next(); // 1
    it2.next(); // 10
    it2.previous(); // 1
    assert(it2.getCurrent() == 1);
    it2.previous(); // 1
    it2.previous(); // 5
    TElem e = it2.getCurrent();
    try {
        it2.previous();
        assert(false);
    }
    catch (std::exception&) {
        assert(true);
    }
    Bag b3;
    BagIterator it3 = b3.iterator();
        try {
            it3.previous();
            assert(false);
        }
        catch (std::exception&) {
            assert(true);
        }
}
