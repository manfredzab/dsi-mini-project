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

/**
 * Leapfrog join trie iterator as described by Todd L Veldhuizen in "Leapfrog Triejoin: A Simple, Worst-Case Optimal Join Algorithm",
 * LogicBlox Technical Report LB1201, December 2012. This class instantiates an abstract multi-way sort-merge join trie iterator with
 * leapfrog join iterators and binary search tree-based trie iterators.
 */
class LeapfrogJoinTrieIterator : public virtual AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>
{
    public:
        LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>(relations, query) { };
        virtual ~LeapfrogJoinTrieIterator() { };

    protected:
        /**
         * Creates a binary search tree-based trie iterator for a given relation.
         * @param relation Input relation.
         * @returns A pointer to the binary search tree-based trie iterator for a given relation.
         */
        virtual BinarySearchTreeTrieIterator* CreateTrieIteratorForRelation(const Relation& relation);

        /**
         * Creates a leapfrog join iterator for given relation trie iterators based on binary search trees.
         * @param trie_iterators A reference to the list of binary search tree-based trie iterators.
         * @returns A pointer to the leapfrog join iterator for given trie iterators.
         */
        virtual LeapfrogJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<BinarySearchTreeTrieIterator*>& trie_iterators);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
