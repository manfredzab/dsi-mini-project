#ifndef LEAPFROG_JOIN_TRIE_ITERATOR_H_
#define LEAPFROG_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "seekable_join_iterator.h"
#include "trie_iterator_interface.h"
#include "sort_merge_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinTrieIterator : public virtual SortMergeJoinTrieIterator
{
    public:
        LeapfrogJoinTrieIterator() { };
        virtual ~LeapfrogJoinTrieIterator() { };

    protected:
        virtual TrieIterator* CreateTrieIteratorForRelation(const Relation& relation);
        virtual JoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TrieIterator*>& trie_iterators);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
