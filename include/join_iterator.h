#ifndef JOIN_ITERATOR_H_
#define JOIN_ITERATOR_H_

#include <vector>
#include "trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class JoinIterator
{
    public:
        JoinIterator(std::vector<TrieIterator*>& iterators);
        virtual ~JoinIterator() { };

        virtual void Init();
        virtual void Search();

        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        virtual void SeekCurrentIteratorToMaxKey();

        std::vector<TrieIterator*>& iterators;
        bool                        at_end;
        int                         key;
        int                         min_key;
        int                         max_key;
        int                         key_multiplicity;
        int                         current_iterator_index;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* JOIN_ITERATOR_H_ */
