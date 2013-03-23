#ifndef LEAPFROG_JOIN_ITERATOR_H_
#define LEAPFROG_JOIN_ITERATOR_H_

#include <vector>
#include "abstract_multiway_sort_merge_join_iterator.h"
#include "binary_search_tree_trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Leapfrog join iterator implementation. It is based on an abstract multiway sort-merge join iterator, with
 * the main difference that it uses the linear iterator portions of the binary tree trie iterator to seek the
 * current iterator to the next candidate key.
 */
class LeapfrogJoinIterator : public virtual AbstractMultiwaySortMergeJoinIterator<BinarySearchTreeTrieIterator>
{
    public:
        LeapfrogJoinIterator(std::vector<BinarySearchTreeTrieIterator*>& iterators);
        virtual ~LeapfrogJoinIterator() { };

        virtual Status Seek(int seek_key);

    protected:
        virtual void PositionCurrentIteratorAtKey(int key);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_ITERATOR_H_ */
