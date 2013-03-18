#ifndef SEEKABLE_JOIN_ITERATOR_H_
#define SEEKABLE_JOIN_ITERATOR_H_

#include <vector>
#include "join_iterator.h"
#include "seekable_trie_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class SeekableJoinIterator : public virtual JoinIterator
{
    public:
        SeekableJoinIterator(std::vector<TrieIterator*>& iterators) : JoinIterator(iterators) { };
        virtual ~SeekableJoinIterator() { };

        virtual Status Seek(int seek_key);
    protected:
        virtual void SeekCurrentIteratorToMaxKey();
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SEEKABLE_JOIN_ITERATOR_H_ */
