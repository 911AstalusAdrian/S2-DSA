#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);

	positionPair pair = m.positionOf(5);  /// element 5 exists on line 1 col 1
    assert(pair.first == 1);
    assert(pair.second == 1);

    positionPair other_pair = m.positionOf(2); /// element 2 does not exist
    assert(other_pair.first == -1);
    assert(other_pair.second == -1);

	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);

    positionPair pair_again = m.positionOf(5);  /// element 5 does not exist anymore
    assert(pair_again.first == -1);
    assert(pair_again.second == -1);

    positionPair pair_once_more = m.positionOf(6);  /// element 6 exists on line 1 col 1
    assert(pair_once_more.first == 1);
    assert(pair_once_more.second == 1);

	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}