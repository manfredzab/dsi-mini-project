#ifndef SORT_MERGE_JOIN_H_
#define SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "trie_iterator.h"
#include "join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class SortMergeJoinTrieIterator : public virtual ITrieIterator<int>
{
    public:
        SortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) : depth(0), number_of_join_attributes(0), number_of_result_attributes(0), relations(relations), query(query) { };
        virtual ~SortMergeJoinTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Multiplicity(int* result);
        virtual Status Next();
        virtual bool   AtEnd();
        virtual int    Depth();

    protected:
        virtual bool           AtRoot();
        virtual ITrieIterator<int>* CreateTrieIteratorForRelation(const Relation& relation);
        virtual IJoinIterator<int>* CreateJoinIteratorForTrieIterators(std::vector<ITrieIterator*>& trie_iterators);

        int                                         depth;
        int                                         number_of_join_attributes;
        int                                         number_of_result_attributes;
        std::map<std::string, ITrieIterator*>       trie_iterator_for_relation;
        std::map<int, std::vector<ITrieIterator*> > trie_iterators_for_depth;
        std::map<int, IJoinIterator*>               join_iterator_for_depth;
        std::vector<int>                            key_multiplicity_stack;

    private:
        const std::map<std::string, Relation*>& relations;
        const Query&                            query;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SORT_MERGE_JOIN_H_ */
