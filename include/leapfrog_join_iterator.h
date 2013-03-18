#ifndef LEAP_FROG_JOIN_ITERATOR_H_
#define LEAP_FROG_JOIN_ITERATOR_H_

#include <vector>
#include "trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class LeapfrogJoinIterator
{
    public:
        LeapfrogJoinIterator(std::vector<TrieIterator*>& iterators);
        virtual ~LeapfrogJoinIterator() { };

        virtual void Init();
        virtual void Search();

        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_result);
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

} // namespace uk_ac_ox_cs_c875114

#endif /* LEAP_FROG_JOIN_ITERATOR_H_ */
