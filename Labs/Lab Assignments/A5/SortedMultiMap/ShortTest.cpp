#include <assert.h>
#include "ValueIterator.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}


void testValueIterator(){
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.add(1,2);
    smm.add(1,3);
    smm.add(1,1);
    smm.add(2,3);
    smm.add(5,6);
    smm.add(4,3);
    smm.add(4,4);
    smm.add(11,2);
    smm.add(7,7);
    ValueIterator vi = ValueIterator(smm, 1);
    int c = 0;
    vi.first();
    while(vi.valid()){
        c += 1;
        vi.next();
    }
    assert(c == 3);

    ValueIterator vi2 = ValueIterator(smm, 3);
    vi2.first();
    int c2 = 0;
    while(vi.valid()){
        c2 += 1;
        vi2.next();
    }
    assert(c2 == 0);
}
