#ifndef ITERATOR_H_
#define ITERATOR_H_

template <class T>
class IIterator
{
public:
    virtual ~IIterator() {}

    virtual T Key()          = 0;
    virtual void Seek(T key) = 0;
    virtual void Next()      = 0;
    virtual bool AtEnd()     = 0;
};

#endif /* ITERATOR_H_ */
