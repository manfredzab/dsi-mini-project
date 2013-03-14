#ifndef TRIE_ITERATOR_H_
#define TRIE_ITERATOR_H_

#include "status.h"

class ITrieIterator
{
    public:
        virtual ~ITrieIterator() { };

        virtual Status Open()           = 0;
        virtual Status Up()             = 0;
        virtual Status Key(int* result) = 0;
        virtual Status Next()           = 0;
        virtual bool   AtEnd()          = 0;
};


#endif /* TRIE_ITERATOR_H_ */
