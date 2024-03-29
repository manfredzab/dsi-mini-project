#include <algorithm>
#include "../include/leapfrog_join_iterator.h"
#include "../include/binary_search_tree_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

void LeapfrogJoinIterator::PositionCurrentIteratorAtKey(int key)
{
    (dynamic_cast<BinarySearchTreeTrieIterator*>(iterators[current_iterator_index]))->Seek(key);
}

Status LeapfrogJoinIterator::Seek(int seek_key)
{
    (dynamic_cast<BinarySearchTreeTrieIterator*>(iterators[current_iterator_index]))->Seek(seek_key);

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
