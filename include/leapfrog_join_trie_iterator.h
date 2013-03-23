#ifndef LEAPFROG_JOIN_TRIE_ITERATOR_H_
#define LEAPFROG_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>
#include "relation.h"
#include "query.h"
#include "status.h"
#include "abstract_multiway_sort_merge_join_trie_iterator.h"
#include "leapfrog_join_iterator.h"
#include "binary_search_tree_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinTrieIterator : public virtual AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>
{
    public:
        LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>(relations, query) { };
        virtual ~LeapfrogJoinTrieIterator() { };

    protected:
        virtual BinarySearchTreeTrieIterator* CreateTrieIteratorForRelation(const Relation& relation);
        virtual LeapfrogJoinIterator*         CreateJoinIteratorForTrieIterators(std::vector<BinarySearchTreeTrieIterator*>& trie_iterators);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
