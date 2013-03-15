#ifndef SORT_MERGE_JOIN_H_
#define SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include <vector>
#include "relation.h"
#include "query.h"
#include "status.h"
#include "trie_iterator.h"
#include "simple_trie_iterator.h"
#include "sort_merge_join_iterator.h"

//#include "join.h"

class SortMergeJoinTrieIterator : public ITrieIterator
{
    public:
        SortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual ~SortMergeJoinTrieIterator();

        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();

    private:
        bool AtRoot();

        int                                              depth;
        int                                              number_of_join_attributes;
        int                                              number_of_result_attributes;
//        std::vector<int>                                 key_multiplicities;
        std::map<std::string, SimpleTrieIterator*>       trie_iterator_for_relation;
        std::map<int, std::vector<SimpleTrieIterator*> > trie_iterators_for_depth;
        std::map<int, SortMergeJoinIterator*>            join_iterator_for_depth;
};

#endif /* SORT_MERGE_JOIN_H_ */
