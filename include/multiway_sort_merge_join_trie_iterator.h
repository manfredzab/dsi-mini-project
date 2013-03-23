#ifndef MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_
#define MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>
#include "abstract_multiway_sort_merge_join_trie_iterator.h"
#include "multiway_sort_merge_join_iterator.h"
#include "trie_trie_iterator.h"
#include "relation.h"
#include "query.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Multiway sort-merge join trie iterator. This class provides an implementation to the abstract multi-way sort-merge join trie iterator, by constructing
 * (actual) tries for underlying relation trie iterators. Similarly, it constructs simple join iterators which are then used to scan the trie iterators
 * at the appropriate depths by repeatedly calling Next() method.
 */
class MultiwaySortMergeJoinTrieIterator : public virtual AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>
{
    public:
        MultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>(relations, query) { };
        virtual ~MultiwaySortMergeJoinTrieIterator() { };

    protected:
        /**
         * Creates an iterator over a materialized trie for a given relation.
         * @param relation Input relation.
         * @returns A pointer to the iterator over a materialized trie for a given relation.
         */
        virtual TrieTrieIterator* CreateTrieIteratorForRelation(const Relation& relation);

        /**
         * Creates a multi-way sort-merge join iterator for given relation trie iterators based on materialized tries.
         * @param trie_iterators A reference to the list of materialized trie-based trie iterators.
         * @returns A pointer to the multi-way sort-merge join iterator for given trie iterators.
         */
        virtual MultiwaySortMergeJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TrieTrieIterator*>& trie_iterators);
};

} /* namespace uk_ac_ox_cs_c875114 */
#endif /* MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_ */
