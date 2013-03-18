#ifndef SEEKABLE_TRIE_ITERATOR_H_
#define SEEKABLE_TRIE_ITERATOR_H_

#include "trie_iterator.h"
#include "trie_iterator_interface.h"
#include "relation.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class SeekableTrieIterator : public TrieIterator
{
    public:
        SeekableTrieIterator(const Relation& relation) : TrieIterator(relation) { };
        virtual ~SeekableTrieIterator() { };

        virtual Status Seek(int seek_key);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SEEKABLE_TRIE_ITERATOR_H_ */
