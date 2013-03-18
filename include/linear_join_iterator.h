#ifndef LINEAR_JOIN_ITERATOR_H_
#define LINEAR_JOIN_ITERATOR_H_

#include <vector>
#include "simple_join_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class LinearJoinIterator : public virtual SimpleJoinIterator
{
    public:
        LinearJoinIterator(std::vector<ITrieIterator*>& iterators) : SimpleJoinIterator(iterators) { };
        virtual ~LinearJoinIterator() { };

        virtual Status Seek(int seek_key);
    protected:
        virtual void SeekCurrentIteratorToMaxKey();
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LINEAR_JOIN_ITERATOR_H_ */
