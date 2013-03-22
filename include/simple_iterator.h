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
        virtual Status Multiplicity(int* out_multiplicity);
        virtual Status Next();
        virtual bool   AtEnd();

    protected:
        const int       kTupleSize;
        const Relation& kRelation;

        int current_multiplicity;

    private:
        typename std::vector<Tuple>::const_iterator tuple_iterator;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* SIMPLE_ITERATOR_H_ */
