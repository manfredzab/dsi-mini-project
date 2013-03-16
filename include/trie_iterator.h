#ifndef TRIE_ITERATOR_H_
#define TRIE_ITERATOR_H_

#include "linear_iterator.h"
#include "trie_iterator_interface.h"
#include "relation.h"
#include "status.h"
#include "trie.h"

class TrieIterator : public LinearIterator, public ITrieIterator
{
public:
    TrieIterator(const Relation& relation);
    virtual ~TrieIterator();

    virtual Status Open();
    virtual Status Up();
    virtual Status Key(int* result);
    virtual Status Seek(int seek_key);
    virtual Status Next();
    virtual bool   AtEnd();

    virtual Status Peek(int* result);
private:
    bool AtRoot();

    Trie*     trie;
    TrieNode* current_node;
    bool      at_end;
};

#endif /* TRIE_ITERATOR_H_ */
