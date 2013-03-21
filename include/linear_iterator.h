#ifndef LINEAR_ITERATOR_H_
#define LINEAR_ITERATOR_H_

#include "simple_iterator.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

class LinearIterator : public virtual SimpleIterator
{
    public:
        LinearIterator(Relation& relation);
        virtual ~LinearIterator();
};

} // namespace uk_ac_ox_cs_c875114

#endif /* LINEAR_ITERATOR_H_ */
