#ifndef SIMPLEITERATOR_H_
#define SIMPLEITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

class SimpleIterator
{
    public:
        SimpleIterator(const Relation& relation);
        virtual ~SimpleIterator() { };

        virtual Status Key(int* result);
        virtual Status Next();
        virtual bool   AtEnd();

        int attribute_index;
    protected:
        const Relation&                            relation;
        typename std::vector<int*>::const_iterator tuple_iterator;
        int                                        tuple_size;

};

} // namespace uk_ac_ox_cs_c875114

#endif /* SIMPLEITERATOR_H_ */
