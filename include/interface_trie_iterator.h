#ifndef INTERFACE_TRIE_ITERATOR_H_
#define INTERFACE_TRIE_ITERATOR_H_

#include "interface_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

template <typename T>
class ITrieIterator : public virtual IIterator<T>
{
    public:
        virtual ~ITrieIterator() { };

        virtual Status Open()                    = 0;
        virtual Status Up()                      = 0;
        virtual int    Depth()               = 0;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* INTERFACE_TRIE_ITERATOR_H_ */
