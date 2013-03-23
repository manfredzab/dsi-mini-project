#include <vector>
#include "../include/multiway_sort_merge_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

TrieTrieIterator* MultiwaySortMergeJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new TrieTrieIterator(relation);
}


MultiwaySortMergeJoinIterator* MultiwaySortMergeJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<TrieTrieIterator*>& trie_iterators)
{
    return new MultiwaySortMergeJoinIterator(trie_iterators);
}

} /* namespace uk_ac_ox_cs_c875114 */
