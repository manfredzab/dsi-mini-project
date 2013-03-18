#include <algorithm>
#include "../include/seekable_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

void SeekableJoinIterator::SeekCurrentIteratorToMaxKey()
{
    ((SeekableTrieIterator*)(iterators[current_iterator_index]))->Seek(max_key);
}

Status SeekableJoinIterator::Seek(int seek_key)
{
    ((SeekableTrieIterator*)(iterators[current_iterator_index]))->Seek(seek_key);

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

} // namespace uk_ac_ox_cs_c875114
