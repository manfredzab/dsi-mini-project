#ifndef SIMPLE_RELATION_ITERATOR_H_
#define SIMPLE_RELATION_ITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"

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

    protected:
        const Relation&                            relation;
        typename std::vector<int*>::const_iterator tuple_iterator;
        int                                        tuple_size;

};

} // namespace uk_ac_ox_cs_c875114

#endif /* SIMPLE_RELATION_ITERATOR_H_ */
