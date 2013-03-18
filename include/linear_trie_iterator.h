#ifndef LINEAR_TRIE_ITERATOR_H_
#define LINEAR_TRIE_ITERATOR_H_

#include "simple_trie_iterator.h"
#include "relation.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class LinearTrieIterator : public SimpleTrieIterator
{
    public:
        LinearTrieIterator(const Relation& relation) : SimpleTrieIterator(relation) { };
        virtual ~LinearTrieIterator() { };

        virtual Status Seek(int seek_key);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LINEAR_TRIE_ITERATOR_H_ */
