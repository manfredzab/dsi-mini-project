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

namespace c875114
{

/**
 * Multi-way sort-merge join trie iterator. This class instantiates the abstract multi-way sort-merge join trie iterator, by constructing
 * (actual) tries for underlying relation trie iterators (see TrieTrieIterator). Similarly, it constructs simple join iterators which are then
 * used to scan the trie iterators at the appropriate depths by repeatedly calling Next() method (see MultiwaySortMergeJoinIterator).
 */
class MultiwaySortMergeJoinTrieIterator : public virtual AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>
{
    public:
        MultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual ~MultiwaySortMergeJoinTrieIterator() { };

    protected:
        virtual TrieTrieIterator*              CreateTrieIteratorForRelation(const Relation& relation);
        virtual MultiwaySortMergeJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TrieTrieIterator*>& trie_iterators);
};

} /* namespace c875114 */
#endif /* MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_ */
