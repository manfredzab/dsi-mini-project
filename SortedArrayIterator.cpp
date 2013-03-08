#include <iterator>
#include <iostream>

#include <algorithm>
#include <vector>

#include "SortedArrayIterator.h"

template SortedArrayIterator<int>::SortedArrayIterator(int* elements, int count);

template <typename T>
SortedArrayIterator<T>::SortedArrayIterator(T* elements, int count)
{
    this->elements = new std::vector<T>(elements, elements + count);
    sort(this->elements->begin(), this->elements->end());

    std::copy(this->elements->begin(), this->elements->end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;
    this->currentPosition = this->elements->begin();
}


template <typename T>
SortedArrayIterator<T>::~SortedArrayIterator()
{
    delete this->elements;
}


template <typename T>
T SortedArrayIterator<T>::Key()
{
    return *(this->currentPosition);
}

template <typename T>
void SortedArrayIterator<T>::Seek(T key)
{
    if (!this->AtEnd())
    {
        this->currentPosition = std::lower_bound(this->currentPosition + 1, this->elements->end(), key);
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
    return (this->currentPosition == this->elements->end());
}
