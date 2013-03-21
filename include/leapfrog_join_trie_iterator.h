#ifndef LEAPFROG_JOIN_TRIE_ITERATOR_H_
#define LEAPFROG_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "interface_trie_iterator.h"
#include "interface_iterator.h"
#include "multiway_sort_merge_join_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinTrieIterator : public virtual MultiwaySortMergeJoinTrieIterator
{
    public:
        LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : MultiwaySortMergeJoinTrieIterator(relations, query) { };
        virtual ~LeapfrogJoinTrieIterator() { };

    protected:
        virtual ITrieIterator<int>* CreateTrieIteratorForRelation(const Relation& relation);
        virtual IIterator<int>* CreateJoinIteratorForTrieIterators(std::vector<ITrieIterator*>& trie_iterators);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
