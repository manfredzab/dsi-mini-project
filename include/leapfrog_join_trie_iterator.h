#ifndef LEAPFROG_JOIN_TRIE_ITERATOR_H_
#define LEAPFROG_JOIN_TRIE_ITERATOR_H_

#include <map>
#include <string>
#include <vector>

#include "relation.h"
#include "query.h"
#include "status.h"
#include "trie_iterator_interface.h"
#include "trie_iterator.h"
#include "leapfrog_join_iterator.h"

class LeapfrogJoinTrieIterator : public ITrieIterator
{
    public:
        LeapfrogJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual ~LeapfrogJoinTrieIterator();

        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();

    private:
        bool AtRoot();

        int                                        depth;
        int                                        number_of_join_attributes;
        int                                        number_of_result_attributes;
        std::map<std::string, TrieIterator*>       trie_iterator_for_relation;
        std::map<int, std::vector<TrieIterator*> > trie_iterators_for_depth;
        std::map<int, LeapfrogJoinIterator*>       join_iterator_for_depth;
        std::vector<int>                           key_multiplicity_stack;
};

#endif /* LEAPFROG_JOIN_TRIE_ITERATOR_H_ */
