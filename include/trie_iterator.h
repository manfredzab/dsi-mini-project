#ifndef I_TRIE_ITERATOR_H_
#define I_TRIE_ITERATOR_H_

#include "join_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

template <typename T>
class ITrieIterator : public virtual IJoinIterator<T>
{
    public:
        virtual ~ITrieIterator() { };

        virtual Status Open()                    = 0;
        virtual Status Up()                      = 0;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* I_TRIE_ITERATOR_H_ */
