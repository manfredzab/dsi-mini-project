#ifndef LEAPFROG_JOIN_ITERATOR_H_
#define LEAPFROG_JOIN_ITERATOR_H_

#include <vector>
#include "abstract_multiway_sort_merge_join_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinIterator : public virtual AbstractMultiwaySortMergeJoinIterator
{
    public:
        LeapfrogJoinIterator(std::vector<ITrieIterator<int>*>& iterators) : AbstractMultiwaySortMergeJoinIterator(iterators) { };
        virtual ~LeapfrogJoinIterator() { };

        virtual Status Seek(int seek_key);

    protected:
        virtual void PositionCurrentIteratorAtKey(int key);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_ITERATOR_H_ */
