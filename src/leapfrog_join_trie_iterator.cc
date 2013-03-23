#include <vector>
#include "../include/leapfrog_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

BinarySearchTreeTrieIterator* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new BinarySearchTreeTrieIterator(relation);
}


LeapfrogJoinIterator* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<BinarySearchTreeTrieIterator*>& trie_iterators)
{
    return new LeapfrogJoinIterator(trie_iterators);
}

} /* namespace uk_ac_ox_cs_c875114 */
