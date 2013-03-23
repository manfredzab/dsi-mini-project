#ifndef MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_
#define MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_

#include "abstract_multiway_sort_merge_join_iterator.h"
#include "trie_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Multiway sort-merge join iterator implementation. It is based on an abstract multiway sort-merge join iterator, with
 * the main difference being that it uses the linear iterator portions of the trie-based trie iterator to linearly seek
 * the iterator (by repeatedly calling Next()) iterator to the next candidate key.
 */
class MultiwaySortMergeJoinIterator : public virtual AbstractMultiwaySortMergeJoinIterator<TrieTrieIterator>
{
    public:
        MultiwaySortMergeJoinIterator(std::vector<TrieTrieIterator*>& iterators);
        virtual ~MultiwaySortMergeJoinIterator() { };

    protected:
        virtual void PositionCurrentIteratorAtKey(int key);

};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_ */
