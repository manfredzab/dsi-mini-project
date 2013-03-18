#ifndef SIMPLE_TRIE_ITERATOR_H_
#define SIMPLE_TRIE_ITERATOR_H_

#include "trie_iterator.h"
#include "trie.h"

namespace uk_ac_ox_cs_c875114
{

class SimpleTrieIterator : public virtual ITrieIterator
{
    public:
        SimpleTrieIterator(const Relation& relation);
        virtual ~SimpleTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();
    protected:
        virtual bool AtRoot();

        Trie*     trie;
        TrieNode* current_node;
        int       current_node_multiplicity;
        bool      at_end;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SIMPLE_TRIE_ITERATOR_H_ */
