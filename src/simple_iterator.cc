#include <cstring>
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleIterator::SimpleIterator(const Relation& relation) :
    kTupleSize(relation.attribute_names.size()),
    kRelation(relation)
{
    tuple_iterator = relation.data.begin();
    current_multiplicity = 0;
}


Status SimpleIterator::Key(int** out_key)
{
    if (AtEnd())
    {
        return kFail;
    }

    *out_key = tuple_iterator->key;
    return kOK;
}


Status SimpleIterator::Next()
{
    if (AtEnd())
    {
        return kFail;
    }

    if (current_multiplicity > 1)
    {
        current_multiplicity--;
        return kOK;
    }

    tuple_iterator++;
    if (!AtEnd())
    {
        current_multiplicity = tuple_iterator->multiplicity;
    }

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


Status SimpleIterator::Multiplicity(int* out_multiplicity)
{
    return kNotImplemented;
}

} /* namespace uk_ac_ox_cs_c875114 */
