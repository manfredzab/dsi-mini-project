#ifndef LEAPFROGITERATOR_H_
#define LEAPFROGITERATOR_H_

#include <vector>

#include "IIterator.h"

template <class T>
class LeapfrogIterator// : public IIterator<T>
{
public:
    LeapfrogIterator(std::vector<IIterator<T>*>& iterators); // k - number of relations in a join
    virtual ~LeapfrogIterator();

    virtual T Key();
    virtual void Seek(T key);
    virtual void Next();
    virtual bool AtEnd();
private:
    virtual void Search();

    std::vector<IIterator<T>*>& iterators;

    int k;
    int p;

    bool atEnd;
    T key;
};

#endif /* LEAPFROGITERATOR_H_ */
