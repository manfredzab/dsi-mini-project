#ifndef SIMPLE_RELATION_ITERATOR_H_
#define SIMPLE_RELATION_ITERATOR_H_

#include <list>

#include "status.h"
#include "relation.h"
#include "join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

// TODO: add IRelationIterator
class SimpleRelationIterator
{
    public:
        SimpleRelationIterator(const Relation& relation);
        virtual ~SimpleRelationIterator() { };

        virtual Status Key(int** out_key);
        virtual Status Next();
        virtual bool   AtEnd();

        const int kTupleSize;
    protected:
        const Relation&                          relation;
        typename std::list<int*>::const_iterator tuple_iterator;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* SIMPLE_RELATION_ITERATOR_H_ */
