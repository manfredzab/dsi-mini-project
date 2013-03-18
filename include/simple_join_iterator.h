#ifndef SIMPLE_JOIN_ITERATOR_H_
#define SIMPLE_JOIN_ITERATOR_H_

#include <vector>
#include "join_iterator.h"
#include "trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class SimpleJoinIterator : public virtual IJoinIterator
{
    public:
        SimpleJoinIterator(std::vector<ITrieIterator*>& iterators);
        virtual ~SimpleJoinIterator() { };

        virtual void Init();
        virtual void Search();

        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        virtual void SeekCurrentIteratorToMaxKey();

        std::vector<ITrieIterator*>& iterators;
        bool                         at_end;
        int                          key;
        int                          min_key;
        int                          max_key;
        int                          key_multiplicity;
        int                          current_iterator_index;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SIMPLE_JOIN_ITERATOR_H_ */
