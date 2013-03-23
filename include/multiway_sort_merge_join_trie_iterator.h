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

class MultiwaySortMergeJoinTrieIterator : public virtual AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>
{
    public:
        MultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>(relations, query) { };

        virtual ~MultiwaySortMergeJoinTrieIterator() { };

    protected:
        virtual TrieTrieIterator*              CreateTrieIteratorForRelation(const Relation& relation);
        virtual MultiwaySortMergeJoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TrieTrieIterator*>& trie_iterators);
};

} /* namespace uk_ac_ox_cs_c875114 */
#endif /* MULTIWAY_SORT_MERGE_JOIN_TRIE_ITERATOR_H_ */
