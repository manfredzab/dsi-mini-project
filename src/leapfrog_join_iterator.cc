#include <algorithm>
#include "../include/leapfrog_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

LeapfrogJoinIterator::LeapfrogJoinIterator(vector<BinarySearchTreeTrieIterator*>& iterators) :
    AbstractMultiwaySortMergeJoinIterator<BinarySearchTreeTrieIterator>(iterators)
{
    // Do nothing
};

void LeapfrogJoinIterator::PositionCurrentIteratorAtKey(int key)
{
    iterators[current_iterator_index]->Seek(key);
}


Status LeapfrogJoinIterator::Seek(int seek_key)
{
    iterators[current_iterator_index]->Seek(key);

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
