#include "../include/simple_iterator.h"

SimpleIterator::SimpleIterator(const Relation& relation) : relation(relation)
{
    this->tuple_iterator = this->relation.data.begin();
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
    return (this->tuple_iterator == this->relation.data.end() - 1);
}
