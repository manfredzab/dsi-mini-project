#include "../include/multiway_sort_merge_join_iterator.h"

namespace c875114
{

/**
 * Constructs a multi-way sort-merge join iterator on the given materialized trie-based trie iterators.
 * @param iterators Materialized trie-based iterators which the multi-way sort-merge join iterator
 *                  should use when searching for the next key.
 */
MultiwaySortMergeJoinIterator::MultiwaySortMergeJoinIterator(std::vector<TrieTrieIterator*>& iterators) :
    AbstractMultiwaySortMergeJoinIterator<TrieTrieIterator>(iterators)
{
    // Do nothing
};

/**
 * Finds the least upper bound (LUB) for a given key at the current trie iterator by
 * linear scanning (repeatedly calling Next() until the LUB is found).
 * @param key Key for which the LUB should be found.
 */
void MultiwaySortMergeJoinIterator::PositionCurrentIteratorAtKey(int key)
{
    while ((min_key < key) && !iterators[current_iterator_index]->AtEnd())
    {
        iterators[current_iterator_index]->Next();
        iterators[current_iterator_index]->Key(&min_key);
    }
}

} /* namespace c875114 */
