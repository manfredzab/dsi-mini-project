#ifndef SIMPLE_ITERATOR_H_
#define SIMPLE_ITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"
#include "interface_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class SimpleIterator : IIterator<int*>
{
    public:
        SimpleIterator(const Relation& relation);
        virtual ~SimpleIterator() { };

        virtual Status Init();
        virtual Status Key(int** out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

        const int kTupleSize;
    protected:
        const Relation&                          relation;
        typename std::vector<int*>::const_iterator tuple_iterator;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* SIMPLE_ITERATOR_H_ */
