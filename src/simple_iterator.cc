#include <cstring>
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleIterator::SimpleIterator(const Relation& relation) :
    kTupleSize(relation.attribute_names.size()),
    relation(relation)
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
    return (this->tuple_iterator == this->relation.data.end());
}


Status SimpleIterator::Init()
{
    return kNotSupported;
}


Status SimpleIterator::Multiplicity(int* out_result)
{
    return kNotSupported;
}
} /* namespace uk_ac_ox_cs_c875114 */
