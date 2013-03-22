#ifndef ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_
#define ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_

#include <vector>
#include "interface_iterator.h"
#include "interface_trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class AbstractMultiwaySortMergeJoinIterator : public virtual IIterator<int>
{
    public:
        AbstractMultiwaySortMergeJoinIterator(std::vector<ITrieIterator<int>*>& iterators);
        virtual ~AbstractMultiwaySortMergeJoinIterator() { };

        virtual Status Init();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        virtual void PositionCurrentIteratorAtKey(int key) = 0;
        virtual void Search();

        std::vector<ITrieIterator<int>*>& iterators;
        bool                              at_end;
        int                               key;
        int                               min_key;
        int                               max_key;
        int                               key_multiplicity;
        int                               current_iterator_index;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* ABSTRACT_MULTIWAY_SORT_MERGE_JOIN_ITERATOR_H_ */
