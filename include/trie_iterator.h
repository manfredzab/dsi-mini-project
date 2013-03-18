#ifndef TRIE_ITERATOR_H_
#define TRIE_ITERATOR_H_

#include "linear_iterator.h"
#include "trie_iterator_interface.h"
#include "relation.h"
#include "status.h"
#include "trie.h"

namespace uk_ac_ox_cs_c875114
{

class TrieIterator : public LinearIterator, public ITrieIterator
{
    public:
        TrieIterator(const Relation& relation);
        virtual ~TrieIterator();

        virtual Status Open();
        virtual Status Up();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Seek(int seek_key);
        virtual Status Next();
        virtual bool   AtEnd();
    private:
        bool AtRoot();

        Trie*     trie;
        TrieNode* current_node;
        int       current_node_multiplicity;
        bool      at_end;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* TRIE_ITERATOR_H_ */
