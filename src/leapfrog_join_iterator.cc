#include <algorithm>
#include "../include/leapfrog_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

/**
 * Constructs a leapfrog join iterator on the given binary search tree-based trie iterators.
 * @param iterators Binary search tree-based iterators which the leapfrog join iterator
 *                  should use when searching for the next key.
 */
LeapfrogJoinIterator::LeapfrogJoinIterator(vector<BinarySearchTreeTrieIterator*>& iterators) :
    AbstractMultiwaySortMergeJoinIterator<BinarySearchTreeTrieIterator>(iterators)
{
    // Do nothing
};

/**
 * Finds the least upper bound (LUB) for a given key at the current trie iterator using the
 * binary search tree iterator's Seek() method.
 * @param key Key for which the LUB should be found.
 */
void LeapfrogJoinIterator::PositionCurrentIteratorAtKey(int key)
{
    iterators[current_iterator_index]->Seek(key);
}

/**
 * Seeks to the least upper bound of the seek key. Complexity: \f$O(\log N)\f$ where \f$N\f$ is the number of
 * nodes in the underlying binary search tree. Amortized complexity: \f$O(1 + \log N/m)\f$ for \f$m\f$ accesses
 * of keys in ascending order.
 * @param seek_key Seek key.
 * @returns kOK on success, failure otherwise.
 */
Status LeapfrogJoinIterator::Seek(int seek_key)
{
    iterators[current_iterator_index]->Seek(key);

    if (iterators[current_iterator_index]->AtEnd())
    {
        at_end = true;
    }
    else
    {
        current_iterator_index = (current_iterator_index + 1) % iterators.size();
        Search();
    }

    return (this->AtEnd()) ? kFail : kOK;
}

} /* namespace uk_ac_ox_cs_c875114 */
