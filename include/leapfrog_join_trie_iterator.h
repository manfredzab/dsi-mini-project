#ifndef LEAPFROG_JOIN_TRIE_ITERATOR_H_
#define LEAPFROG_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "trie_iterator.h"
#include "join_iterator.h"
#include "sort_merge_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinTrieIterator : public virtual SortMergeJoinTrieIterator
{
    public:
        LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : SortMergeJoinTrieIterator(relations, query) { };
        virtual ~LeapfrogJoinTrieIterator() { };

    protected:
        virtual ITrieIterator* CreateTrieIteratorForRelation(const Relation& relation);
        virtual IJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<ITrieIterator*>& trie_iterators);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
