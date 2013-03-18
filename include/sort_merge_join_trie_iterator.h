#ifndef SORT_MERGE_JOIN_H_
#define SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "trie_iterator_interface.h"
#include "trie_iterator.h"
#include "join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class SortMergeJoinTrieIterator : public virtual ITrieIterator
{
    public:
        SortMergeJoinTrieIterator() : depth(0), number_of_join_attributes(0), number_of_result_attributes(0) { };
        virtual ~SortMergeJoinTrieIterator();

        virtual void   Init(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        virtual bool          AtRoot();
        virtual TrieIterator* CreateTrieIteratorForRelation(const Relation& relation);
        virtual JoinIterator* CreateJoinIteratorForTrieIterators(std::vector<TrieIterator*>& trie_iterators);

        int                                        depth;
        int                                        number_of_join_attributes;
        int                                        number_of_result_attributes;
        std::map<std::string, TrieIterator*>       trie_iterator_for_relation;
        std::map<int, std::vector<TrieIterator*> > trie_iterators_for_depth;
        std::map<int, JoinIterator*>               join_iterator_for_depth;
        std::vector<int>                           key_multiplicity_stack;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SORT_MERGE_JOIN_H_ */
