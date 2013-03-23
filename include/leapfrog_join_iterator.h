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

        /**
         * Seeks to the least upper bound of the seek key. Complexity: O(log N) where N is the number of
         * nodes in the underlying binary search tree. Amortized complexity: O(1 + log N/m) for m accesses
         * of keys in ascending order.
         * @param seek_key Seek key.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Seek(int seek_key);

    protected:
        /**
         * Finds the least upper bound (LUB) for a given key at the current trie iterator using the
         * binary search tree iterator's Seek() method.
         * @param key Key for which the LUB should be found.
         */
        virtual void PositionCurrentIteratorAtKey(int key);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_ITERATOR_H_ */
