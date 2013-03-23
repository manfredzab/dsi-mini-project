#ifndef SIMPLE_ITERATOR_H_
#define SIMPLE_ITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"
#include "interface_iterator.h"

namespace c875114
{

/**
 * Allows access to the tuples of a given relation in a given order.
 */
class SimpleIterator : IIterator<int*>
{
    public:
        SimpleIterator(const Relation& relation);
        virtual ~SimpleIterator() { };

        virtual Status Key(int** out_key);
        virtual Status Init();
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        const int       kTupleSize;
        const Relation& kRelation;

    private:
        typename std::vector<int*>::const_iterator tuple_iterator;
};

} /* namespace c875114 */

#endif /* SIMPLE_ITERATOR_H_ */
