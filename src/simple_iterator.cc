#include "../include/simple_iterator.h"

template SimpleIterator<int*>::SimpleIterator(const std::vector<int*>& data);


template <typename T>
SimpleIterator<T>::SimpleIterator(const std::vector<T>& data) : tuple_data(data)
{
    this->tuple_iterator = data.begin();
    this->attribute_index = 0;
}


template <typename T>
Status SimpleIterator<T>::Key(T result)
{
    *result = (*this->tuple_iterator)[this->attribute_index];
    return kOK;
}

template <typename T>
Status SimpleIterator<T>::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    this->tuple_iterator++;
    return kOK;
}

template <typename T>
bool SimpleIterator<T>::AtEnd()
{
    return (this->tuple_iterator == this->tuple_data.end());
}
