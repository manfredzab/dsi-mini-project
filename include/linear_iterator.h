#ifndef LINEAR_ITERATOR_H_
#define LINEAR_ITERATOR_H_

#include "simple_iterator.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class LinearIterator : public SimpleIterator
{
    public:
        LinearIterator(const Relation& relation) : SimpleIterator(relation) { }
        virtual ~LinearIterator() { }

        virtual Status Seek(int* seek_key);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LINEAR_ITERATOR_H_ */
