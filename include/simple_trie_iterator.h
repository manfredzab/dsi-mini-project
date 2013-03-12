#ifndef SIMPLE_TRIE_ITERATOR_H_
#define SIMPLE_TRIE_ITERATOR_H_

#include "simple_iterator.h"
#include "trie.h"

class SimpleTrieIterator : public virtual SimpleIterator
{
    public:
        SimpleTrieIterator(const Relation& relation);
        virtual ~SimpleTrieIterator();

        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();
    private:
        bool AtRoot();

        Trie* trie;
        TrieNode* current_node;
};

#endif /* SIMPLE_TRIE_ITERATOR_H_ */
