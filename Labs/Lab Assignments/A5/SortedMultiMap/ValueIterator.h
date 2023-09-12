#pragma once
#include <vector>
#include <utility>
#include "SMMIterator.h"


class ValueIterator{
    friend class SortedMultiMap;

private:
    const SortedMultiMap& map;
    const TKey key;

    TValue* values;
    int cap;
    TValue current;

public:
    ValueIterator(const SortedMultiMap& map, TKey k);
    void first();
    void next();
    bool valid() const;
    TValue getCurrent() const;
};