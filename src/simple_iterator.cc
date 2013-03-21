#include <cstring>
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleIterator::SimpleIterator(const Relation& relation) :
    kTupleSize(relation.attribute_names.size()),
    kRelation(relation)
{
    this->tuple_iterator = relation.data.begin();
}


Status SimpleIterator::Key(int** out_key)
{
    if (this->AtEnd())
    {
        return kFail;
    }

    *out_key = *this->tuple_iterator;
    return kOK;
}


Status SimpleIterator::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    this->tuple_iterator++;
    return kOK;
}


bool SimpleIterator::AtEnd()
{
    return (this->tuple_iterator == this->kRelation.data.end());
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
