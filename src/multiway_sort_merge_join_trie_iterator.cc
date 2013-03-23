#include <vector>
#include "../include/multiway_sort_merge_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

/**
 * Constructs a multi-way sort-merge join trie iterator which traverses the non-materialized
 * join result trie for a given join query/relations.
 * @param relations Relations which should be joined.
 * @param query     Join query.
 */
MultiwaySortMergeJoinTrieIterator::MultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) :
    AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>(relations, query)
{
    // Do nothing
};

/**
 * Creates an iterator over a materialized trie for a given relation.
 * @param relation Input relation.
 * @returns A pointer to the iterator over a materialized trie for a given relation.
 */
TrieTrieIterator* MultiwaySortMergeJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new TrieTrieIterator(relation);
}

/**
 * Creates a multi-way sort-merge join iterator for given relation trie iterators based on materialized tries.
 * @param trie_iterators A reference to the list of materialized trie-based trie iterators.
 * @returns A pointer to the multi-way sort-merge join iterator for given trie iterators.
 */
MultiwaySortMergeJoinIterator* MultiwaySortMergeJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<TrieTrieIterator*>& trie_iterators)
{
    return new MultiwaySortMergeJoinIterator(trie_iterators);
}

} /* namespace uk_ac_ox_cs_c875114 */
