#include <cstring>
#include "../include/simple_relation_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleRelationIterator::SimpleRelationIterator(const Relation& relation) :
        kTupleSize(relation.attribute_names.size()),
        relation(relation)
{
    this->tuple_iterator = relation.data.begin();
}


Status SimpleRelationIterator::Key(int** out_key)
{
    if (this->AtEnd())
    {
        return kFail;
    }

    *out_key = *this->tuple_iterator;
    return kOK;
}


Status SimpleRelationIterator::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    this->tuple_iterator++;
    return kOK;
}


bool SimpleRelationIterator::AtEnd()
{
    return (this->tuple_iterator == this->relation.data.end());
}

} // namespace uk_ac_ox_cs_c875114
