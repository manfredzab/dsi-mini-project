#include <cstring>
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleIterator::SimpleIterator(const Relation& relation) :
    kTupleSize(relation.attribute_names.size()),
    kRelation(relation)
{
    tuple_iterator = relation.data.begin();
}


Status SimpleIterator::Key(int** out_key)
{
    if (AtEnd())
    {
        return kFail;
    }

    *out_key = *tuple_iterator;
    return kOK;
}


Status SimpleIterator::Next()
{
    if (AtEnd())
    {
        return kFail;
    }

    tuple_iterator++;
    return kOK;
}


bool SimpleIterator::AtEnd()
{
    return (tuple_iterator == kRelation.data.end());
}


Status SimpleIterator::Init()
{
    return kNotImplemented;
}


Status SimpleIterator::Multiplicity(int* out_result)
{
    return kNotImplemented;
}

} /* namespace uk_ac_ox_cs_c875114 */
