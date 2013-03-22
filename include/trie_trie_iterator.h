#ifndef TRIE_TRIE_ITERATOR_H_
#define TRIE_TRIE_ITERATOR_H_

#include "interface_trie_iterator.h"
#include "trie.h"

namespace uk_ac_ox_cs_c875114
{

class TrieTrieIterator : public virtual ITrieIterator<int>
{
    public:
        TrieTrieIterator(const Relation& relation);
        virtual ~TrieTrieIterator();

        virtual Status Init();
        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();
        virtual int    Arity();

    protected:
        virtual bool AtRoot();

        const int kArity;

        Trie*     trie;
        TrieNode* current_node;
        int       current_node_multiplicity;
        bool      at_end;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* TRIE_TRIE_ITERATOR_H_ */
