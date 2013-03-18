#ifndef I_TRIE_ITERATOR_H_
#define I_TRIE_ITERATOR_H_

#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class ITrieIterator
{
    public:
        virtual ~ITrieIterator() { };

        virtual Status Init()                    = 0;
        virtual Status Open()                    = 0;
        virtual Status Up()                      = 0;
        virtual Status Key(int* result)          = 0;
        virtual Status Multiplicity(int* result) = 0;
        virtual Status Next()                    = 0;
        virtual bool   AtEnd()                   = 0;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* I_TRIE_ITERATOR_H_ */
