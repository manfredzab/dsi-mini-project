#ifndef SIMPLEITERATOR_H_
#define SIMPLEITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"

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

#endif /* SIMPLEITERATOR_H_ */
