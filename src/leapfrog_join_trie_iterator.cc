#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/leapfrog_join_iterator.h"
#include "../include/binary_search_tree_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

ITrieIterator<int>* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new BinarySearchTreeTrieIterator(relation);
}


IIterator<int>* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<ITrieIterator*>& trie_iterators)
{
    return new LeapfrogJoinIterator(trie_iterators);
}

} /* namespace uk_ac_ox_cs_c875114 */
