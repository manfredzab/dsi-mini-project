#include <vector>
#include "../include/leapfrog_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

/**
 * Constructs a leapfrog join trie iterator which traverses the non-materialized join result trie
 * for a given join query/relations.
 * @param relations Relations which should be joined.
 * @param query     Join query.
 */
LeapfrogJoinTrieIterator::LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) :
    AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>(relations, query)
{
    // Do nothing
};

/**
 * Creates a binary search tree-based trie iterator for a given relation.
 * @param relation Input relation.
 * @returns A pointer to the binary search tree-based trie iterator for a given relation.
 */
BinarySearchTreeTrieIterator* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new BinarySearchTreeTrieIterator(relation);
}

/**
 * Creates a leapfrog join iterator for given relation trie iterators based on binary search trees.
 * @param trie_iterators A reference to the list of binary search tree-based trie iterators.
 * @returns A pointer to the leapfrog join iterator for given trie iterators.
 */
LeapfrogJoinIterator* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<BinarySearchTreeTrieIterator*>& trie_iterators)
{
    return new LeapfrogJoinIterator(trie_iterators);
}

} /* namespace uk_ac_ox_cs_c875114 */
