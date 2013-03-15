#ifndef SIMPLE_TRIE_ITERATOR_H_
#define SIMPLE_TRIE_ITERATOR_H_

#include "simple_iterator.h"
#include "trie_iterator.h"
#include "trie.h"

// TODO: implement without building a tree (using just the seeks of the simple iterator);
//       use this implementation as basis for trie iterator for leapfrog.
class SimpleTrieIterator : public ITrieIterator // : public virtual SimpleIterator
{
    public:
        SimpleTrieIterator(const Relation& relation);
        virtual ~SimpleTrieIterator();

        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Next();
        virtual Status Peek(int* result);
        virtual bool   AtEnd();
    private:
        bool AtRoot();

        Trie*     trie;
        TrieNode* current_node;
        bool      at_end;
};

#endif /* SIMPLE_TRIE_ITERATOR_H_ */
