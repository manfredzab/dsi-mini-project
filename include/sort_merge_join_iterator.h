#ifndef SORT_MERGE_JOIN_ITERATOR_H_
#define SORT_MERGE_JOIN_ITERATOR_H_

#include <vector>
#include "simple_trie_iterator.h"
#include "status.h"

class SortMergeJoinIterator
{
    public:
        SortMergeJoinIterator(std::vector<SimpleTrieIterator*>& iterators);
        virtual ~SortMergeJoinIterator() { };

        virtual void Init();
        virtual void Search();
        virtual int KeyMultiplicity();

        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();
    private:
        std::vector<SimpleTrieIterator*>& iterators;
        bool                              at_end;
        int                               key;
        int                               key_multiplicity;
        int                               current_iterator;
};

#endif /* SORT_MERGE_JOIN_ITERATOR_H_ */
