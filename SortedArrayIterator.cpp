#include <iostream>
#include <iterator>

#include <algorithm>
#include <vector>

#include "SortedArrayIterator.h"

template <typename T>
SortedArrayIterator<T>::SortedArrayIterator(T* elements, int count)
{
    this->elements = new std::vector<T>(elements, elements + count);
    sort(this->elements->begin(), this->elements->end());

    // copy(this->elements->begin(), this->elements->end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;
    this->currentPosition = 0;
}


template <typename T>
SortedArrayIterator<T>::~SortedArrayIterator()
{
    delete this->elements;
}


template <typename T>
T SortedArrayIterator<T>::Key()
{
    return this->elements->at(this->currentPosition);
}

template <typename T>
void SortedArrayIterator<T>::Seek(T key)
{
    if (!this->AtEnd())
    {
        typename std::vector<T>::iterator lowerBoundIterator;
        lowerBoundIterator = std::lower_bound(this->elements->begin() + this->currentPosition + 1, this->elements->end(), key);

        this->currentPosition = lowerBoundIterator - this->elements->begin();
    }
}

template <typename T>
void SortedArrayIterator<T>::Next()
{
    if (!this->AtEnd())
    {
        this->currentPosition++;
    }
}

template <typename T>
bool SortedArrayIterator<T>::AtEnd()
{
    return (this->currentPosition == (int)this->elements->size());
}
