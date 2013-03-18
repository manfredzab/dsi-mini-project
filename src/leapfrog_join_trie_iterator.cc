#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/seekable_trie_iterator.h"
#include "../include/seekable_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

TrieIterator* LeapfrogJoinTrieIterator::CreateTrieIteratorForRelation(const Relation& relation)
{
    return new SeekableTrieIterator(relation);
}


JoinIterator* LeapfrogJoinTrieIterator::CreateJoinIteratorForTrieIterators(vector<TrieIterator*>& trie_iterators)
{
    return new SeekableJoinIterator(trie_iterators);
}

} // namespace uk_ac_ox_cs_c875114
