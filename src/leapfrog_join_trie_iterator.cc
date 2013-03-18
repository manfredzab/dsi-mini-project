#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/linear_trie_iterator.h"
#include "../include/linear_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

ITrieIterator* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new LinearTrieIterator(relation);
}


IJoinIterator* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<ITrieIterator*>& trie_iterators)
{
    return new LinearJoinIterator(trie_iterators);
}

} // namespace uk_ac_ox_cs_c875114
