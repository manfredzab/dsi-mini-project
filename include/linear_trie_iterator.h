// TODO: remove file

#ifndef LINEAR_TRIE_ITERATOR_H_
#define LINEAR_TRIE_ITERATOR_H_

#include "trie_trie_iterator.h"
#include "relation.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

// TODO: remove and replace by BinarySearchTreeTrieIterator
class LinearTrieIterator : public TrieTrieIterator
{
    public:
        LinearTrieIterator(const Relation& relation) : TrieTrieIterator(relation) { };
        virtual ~LinearTrieIterator() { };

        virtual Status Seek(int seek_key);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LINEAR_TRIE_ITERATOR_H_ */
