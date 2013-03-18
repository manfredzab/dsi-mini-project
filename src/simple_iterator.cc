#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

SimpleIterator::SimpleIterator(const Relation& relation) : relation(relation)
{
    this->tuple_iterator = relation.data.begin();
    this->tuple_size = relation.attribute_names.size();

    this->attribute_index = 0;
}


Status SimpleIterator::Key(int* result)
{
    *result = (*this->tuple_iterator)[this->attribute_index];

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

} // namespace uk_ac_ox_cs_c875114
