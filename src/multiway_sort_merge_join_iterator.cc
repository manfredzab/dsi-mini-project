#include "../include/multiway_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

void MultiwaySortMergeJoinIterator::PositionCurrentIteratorAtKey(int key)
{
    while ((min_key < key) && !iterators[current_iterator_index]->AtEnd())
    {
        iterators[current_iterator_index]->Next();
        iterators[current_iterator_index]->Key(&min_key);
    }
}

} /* namespace uk_ac_ox_cs_c875114 */
