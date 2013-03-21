#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/linear_trie_iterator.h"
#include "../include/leapfrog_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

ITrieIterator<int>* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new LinearTrieIterator(relation);
}


IIterator<int>* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<ITrieIterator*>& trie_iterators)
{
    return new LeapfrogJoinIterator(trie_iterators);
}

} // namespace uk_ac_ox_cs_c875114
