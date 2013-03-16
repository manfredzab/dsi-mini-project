#ifndef LEAP_FROG_JOIN_ITERATOR_H_
#define LEAP_FROG_JOIN_ITERATOR_H_

#include <vector>
#include "trie_iterator.h"
#include "status.h"

class LeapfrogJoinIterator
{
    public:
        LeapfrogJoinIterator(std::vector<TrieIterator*>& iterators);
        virtual ~LeapfrogJoinIterator() { };

        virtual void Init();
        virtual void Search();

        virtual Status Key(int* result);
        virtual Status Next();
        virtual Status Seek(int seek_key);
        virtual bool   AtEnd();
    private:
        std::vector<TrieIterator*>& iterators;
        bool                        at_end;
        int                         key;
        int                         key_multiplicity;
        int                         current_iterator_index;
};

#endif /* LEAP_FROG_JOIN_ITERATOR_H_ */
