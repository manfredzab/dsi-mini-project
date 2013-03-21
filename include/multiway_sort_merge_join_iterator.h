#ifndef MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_
#define MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_

#include "abstract_multiway_sort_merge_join_iterator.h"
#include "interface_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class MultiwaySortMergeJoinIterator : public virtual AbstractMultiwaySortMergeJoinIterator
{
    public:
        MultiwaySortMergeJoinIterator(std::vector<ITrieIterator<int>*>& iterators) : AbstractMultiwaySortMergeJoinIterator(iterators) { };
        virtual ~MultiwaySortMergeJoinIterator() { };
    protected:
        virtual void PositionCurrentIteratorAtKey(int key);

};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_ */
