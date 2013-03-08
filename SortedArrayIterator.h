#ifndef SORTEDARRAYITERATOR_H_
#define SORTEDARRAYITERATOR_H_

#include <vector>
#include "IIterator.h"

template <class T>
class SortedArrayIterator : public IIterator<T>
{
public:
    SortedArrayIterator(T* elements, int count);
    virtual ~SortedArrayIterator();

    virtual T Key();
    virtual void Seek(T key);
    virtual void Next();
    virtual bool AtEnd();
private:
    std::vector<T>* elements;
    typename std::vector<T>::iterator currentPosition;
};

#endif /* SORTEDARRAYITERATOR_H_ */
